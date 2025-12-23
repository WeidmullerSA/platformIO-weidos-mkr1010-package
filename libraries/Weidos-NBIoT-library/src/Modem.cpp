/*
  This file is part of the MKR NB library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Modem.h"
#include <HardwareSerialPIC.h>

#define MODEM_MIN_RESPONSE_OR_URC_WAIT_TIME_MS 20

ModemUrcHandler* ModemClass::_urcHandlers[MAX_URC_HANDLERS] = { NULL };
Print* ModemClass::_debugPrint = NULL;

ModemClass::ModemClass(HardwareSerial& uart, unsigned long baud, int resetPin, int powerOnPin, int vIntPin) :
  _uart(&uart),
  _baud(baud),
  _resetPin(resetPin),
  _powerOnPin(powerOnPin),
  _vIntPin(vIntPin),
  _lastResponseOrUrcMillis(0),
  _atCommandState(AT_COMMAND_IDLE),
  _ready(1),
  _responseDataStorage(NULL)
{
  _buffer.reserve(64);
}

void ModemClass::setVIntPin(int vIntPin)
{
  // Allow setting only if unset, used to track state
  if (_vIntPin==SARA_VINT_OFF || _vIntPin==SARA_VINT_ON) {
    _vIntPin=vIntPin;
  }
}

int ModemClass::isPowerOn()
{
  if (_vIntPin==SARA_VINT_OFF) {
    return 0;
  } else if (_vIntPin==SARA_VINT_ON) {
    return 1;
  }
  return digitalRead(_vIntPin);
}

int ModemClass::begin(bool restart, bool softreset)
{
  #ifdef ESP32
    pinMode(SARA_RESETN, OUTPUT);
    pinMode(SARA_PWR_ON, OUTPUT);
  #endif

  digitalWrite(_resetPin, LOW);

  if (restart) {
    shutdown();
    end();
  } else if (softreset) {
    reset();
    delay(20000);
  }

  _uart->begin(_baud);

  // power on module
  if (!isPowerOn()) {
    digitalWrite(_powerOnPin, HIGH);
    delay(300); // Datasheet says power-on pulse should be >=150ms, <=3200ms
    digitalWrite(_powerOnPin, LOW);
    setVIntPin(SARA_VINT_ON);
  } 

  delay(8000);

  //Set Baudrate to 38400
  sendf("AT+IPR=%ld", 38400); 
  delay(100);   
  _uart->end();
  delay(100);
  _uart->begin(16);

  if (!autosense()) {
    return 0;
  }

  return 1;
}

int ModemClass::shutdown()
{
  // AT command shutdown
  if (isPowerOn()) {
    send("AT+CPWROFF");
    if (waitForResponse(40000) != 1) {
      return 0;
    }
    setVIntPin(SARA_VINT_OFF);
  }
  return 1;
}

void ModemClass::end()
{
  _uart->end();
  // Hardware pin power off
  if (isPowerOn()) {
    digitalWrite(_powerOnPin, HIGH);
    delay(1500); // Datasheet says power-off pulse should be >=1500ms
    digitalWrite(_powerOnPin, LOW);
    setVIntPin(SARA_VINT_OFF);
  }
}

void ModemClass::hardReset()
{
  // Hardware pin reset, only use in EMERGENCY
  Serial.println("Doing hard reset");
  digitalWrite(_resetPin, HIGH);
  delay(10000); // Datasheet says 10s min to trigger module abrupt emergency switch off
  digitalWrite(_resetPin, LOW);
  setVIntPin(SARA_VINT_OFF);
}

void ModemClass::debug()
{
  debug(Serial);
}

void ModemClass::debug(Print& p)
{
  _debugPrint = &p;
}

void ModemClass::noDebug()
{
  _debugPrint = NULL;
}

int ModemClass::autosense(unsigned long timeout)
{
  for (unsigned long start = millis(); (millis() - start) < timeout;) {
    if (noop() == 1) {
      return 1;
    }

    delay(100);
  }

  return 0;
}

int ModemClass::autobaud()
{

  #ifdef ESP32
    pinMode(SARA_RESETN, OUTPUT);
    pinMode(SARA_PWR_ON, OUTPUT);
  #endif

  digitalWrite(_resetPin, LOW);
  
  // power on module
  if (!isPowerOn()) {
    digitalWrite(_powerOnPin, HIGH);
    delay(300); // Datasheet says power-on pulse should be >=150ms, <=3200ms
    digitalWrite(_powerOnPin, LOW);
    setVIntPin(SARA_VINT_ON);
  }

  delay(8000);
  
  // Equal to baud: {38400, 115200, 57600, 9600, 19200, 4800, 2400, 1200, 230400};
  const uint8_t pos_baud[] = {16, 19, 17, 14, 15, 13, 12, 11, 10, 20};
  int baudrate;

  for (uint8_t i = 0; i < sizeof(pos_baud); i++) {
    baudrate = (int) pos_baud[i];
    _uart->begin(baudrate);
    
    delay(100);
    
    if (autosense(3000)) {
      Serial.print("Baudrate found: ");
      Serial.println(baudrate);
      setBaudRate(baudrate);
      break;
    }

    if (i == sizeof(pos_baud) - 1) {
      Serial.println("Baudrate not found, could not communicate with the module.");
      baudrate = -1;
      break;
    }

    _uart->end();
    delay(100);
  }

  end();
  delay(1000);
  
  return baudrate;
}

int ModemClass::noop()
{
  send("AT");

  return (waitForResponse() == 1);
}

int ModemClass::reset()
{
  send("AT+CFUN=15");

  return (waitForResponse(180000) == 1);
}

size_t ModemClass::write(uint8_t c)
{
  return _uart->write(c);
}

size_t ModemClass::write(const uint8_t* buf, size_t size)
{
  size_t result = _uart->write(buf, size);

  // the R410m echoes the binary data - we don't want it to do so
  size_t ignoreCount = 0;

  while (ignoreCount < result) {
    if (_uart->available()) {
      ignoreCount++;
    }
  }

  return result;
}

void ModemClass::send(const char* command)
{
  // compare the time of the last response or URC and ensure
  // at least 60ms have passed before sending a new command
  unsigned long delta = millis() - _lastResponseOrUrcMillis;
  if(delta < MODEM_MIN_RESPONSE_OR_URC_WAIT_TIME_MS) {
    delay(MODEM_MIN_RESPONSE_OR_URC_WAIT_TIME_MS - delta);
  }

  _uart->println(command);
  _uart->flush();
  _atCommandState = AT_COMMAND_IDLE;
  _ready = 0;
}

void ModemClass::sendf(const char *fmt, ...)
{
  char buf[BUFSIZ];

  va_list ap;
  va_start((ap), (fmt));
  vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
  va_end(ap);
  send(buf);
}

int ModemClass::waitForPrompt(unsigned long timeout)
{
  for (unsigned long start = millis(); (millis() - start) < timeout;){
    while (_uart->available()) {
      char c = _uart->read();
      _buffer += c;

      if (_buffer.endsWith(">")) {
        return 1;
      }
    }
  }
  return -1;
}

int ModemClass::waitForResponse(unsigned long timeout, String* responseDataStorage)
{
  _responseDataStorage = responseDataStorage;
  for (unsigned long start = millis(); (millis() - start) < timeout;) {
    int r = ready();

    if (r != 0) {
      _responseDataStorage = NULL;
      return r;
    }
  }

  _responseDataStorage = NULL;
  _buffer = "";
  return -1;
}

int ModemClass::ready()
{
  poll();

  return _ready;
}

void ModemClass::poll()
{
  while (_uart->available()) {
    char c = _uart->read();

    if (_debugPrint) {
      _debugPrint->write(c);
    }
    
    _buffer += c;

    switch (_atCommandState) {
    case AT_COMMAND_IDLE:
    default: {

      if (_buffer.startsWith("AT") && _buffer.endsWith("\r\n")) {
	if (_buffer.startsWith("AT+USECMNG=0")) {

	  //Extract the cert length from the received buffer
	  int l_cert = _buffer.substring(_buffer.indexOf(',', 15) + 1, _buffer.indexOf('>', 15)).toInt();

	  if (l_cert + _buffer.indexOf('>', 15) + 2 + 1 <=  _buffer.length()) {
	    _atCommandState = AT_RECEIVING_RESPONSE;
	    _buffer = "";
	  }
	  
	} else {
	  _atCommandState = AT_RECEIVING_RESPONSE;
	  _buffer = "";
	}
      }  else if (_buffer.endsWith("\r\n")) {
	_buffer.trim();
	if (_buffer.length()) {
	  _lastResponseOrUrcMillis = millis();

	  for (int i = 0; i < MAX_URC_HANDLERS; i++) {
	    if (_urcHandlers[i] != NULL) {
	      _urcHandlers[i]->handleUrc(_buffer);
	    }
	  }
	}

	_buffer = "";
      }

      break;
    }

    case AT_RECEIVING_RESPONSE: {
      if (c == '\n') {
	_lastResponseOrUrcMillis = millis();
	int responseResultIndex;

	responseResultIndex = _buffer.lastIndexOf("OK\r\n");

	if (responseResultIndex != -1) {
	  _ready = 1;
	} else {
	  responseResultIndex = _buffer.lastIndexOf("ERROR\r\n");
	  if (responseResultIndex != -1) {
	    _ready = 2;
	  } else {
	    responseResultIndex = _buffer.lastIndexOf("NO CARRIER\r\n");
	    if (responseResultIndex != -1) {
	      _ready = 3;
	    } else {
	      responseResultIndex = _buffer.lastIndexOf("CME ERROR");
	      if (responseResultIndex != -1) {
		_ready = 4;
	      }
	    }
	  }
	}

	if (_ready != 0) {
	  if (_responseDataStorage != NULL) {
	    if (_ready > 1) {
	      _buffer.substring(responseResultIndex);
	    } else {
	      _buffer.remove(responseResultIndex);
	    }
	    _buffer.trim();

	    *_responseDataStorage = _buffer;

	    _responseDataStorage = NULL;
	  }

	  _atCommandState = AT_COMMAND_IDLE;
	  _buffer = "";
	  return;
	}
      }
      break;
    }
    }
  }
}

void ModemClass::setResponseDataStorage(String* responseDataStorage)
{
  _responseDataStorage = responseDataStorage;
}

void ModemClass::addUrcHandler(ModemUrcHandler* handler)
{
  for (int i = 0; i < MAX_URC_HANDLERS; i++) {
    if (_urcHandlers[i] == NULL) {
      _urcHandlers[i] = handler;
      break;
    }
  }
}

void ModemClass::removeUrcHandler(ModemUrcHandler* handler)
{
  for (int i = 0; i < MAX_URC_HANDLERS; i++) {
    if (_urcHandlers[i] == handler) {
      _urcHandlers[i] = NULL;
      break;
    }
  }
}

void ModemClass::setBaudRate(unsigned long baud)
{
  _baud = baud;
}

ModemClass MODEM(SerialSARA, 19, SARA_RESETN, SARA_PWR_ON, SARA_VINT);
