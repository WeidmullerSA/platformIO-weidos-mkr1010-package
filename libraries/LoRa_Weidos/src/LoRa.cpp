/*
   Copyright (c) 2020 Boot&Work Corp., S.L. All rights reserved

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LoRa.h"
#ifdef HAVE_RN2XX3
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <HardwareSerialPIC.h>
#include <rn2xx3.h>


LoRaClass::LoRaClass(HardwareSerial& serial) : _serial(serial), rn2xx3(serial) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LoRaClass::begin() {
	
  LoRaClass::reset();
  delay(250);
  _serial.begin(HardwareSerialPIC::BaudRate_57600);
	return;
}

void LoRaClass::reset(){
  pinMode(RN2XX3_RESET_PIN, OUTPUT);
	digitalWrite(RN2XX3_RESET_PIN, HIGH);

	digitalWrite(RN2XX3_RESET_PIN, LOW);
	delay(10);
	digitalWrite(RN2XX3_RESET_PIN, HIGH);
	delay(10);
}

TX_RETURN_TYPE LoRaClass::send(const String& data, bool confirmed){
  if(confirmed) return txCnf(data);
  else return txUncnf(data);
}

String LoRaClass::radioRx(){
  sendRawCommand(F("mac pause"));
  sendRawCommand(F("radio rx 0"));
  String data = _serial.readStringUntil('\n');

  if(data.length()>0){
    if(data.startsWith("radio_rx")) data.remove(0, 10);
    return data;
  }else{
    return "";
  }
}

RadioError LoRaClass::radioTx(const String& data){
  sendRawCommand(F("mac pause"));

  String response;
  response.reserve(14);
  response = sendRawCommand("radio tx " + data);
  if(response.equals("invalid_param")) return RADIO_INVALID_PARAM;
  if(response.equals("busy")) return RADIO_BUSY;

  response = _serial.readStringUntil('\n');  //Getting second respons
  if(response.equals("radio_err")) return RADIO_TIMEOUT;

  return RADIO_OK;
}

LoRaClass LoRa(SerialPIC);
#endif
