/**
Copyright (C) 2021 Weidmüller SA. All rights reserved.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
  RS485 Receive example

  This sketch receives data over RS485 interface and outputs the data to the Serial Monitor.

  DIP switches MUST be configured to use RS485:
  SW1: 4=ON 1,2,3=indifferent
  SW2: 1=OFF, 2=OFF, 3=ON, 4=ON

  Example RS485_send (File/Examples/RS485/RS485_send) can be used in a second Weidos to receive data from it. Both Weidos'
  DIP switches MUST be configured to use RS485. Wire pin11 <-> pin11 and pin12 <-> pin12.
  
  WARNING!!! DIP switches must be configured to use RS485 prior to ANY WIRING with your device POWERED OFF.
  WARNING!!! Not following this instructions may damage your device.
  WARNING!!! Check User Manual for more information.
*/

#include <ArduinoRS485.h>

#define BAUDRATE 115200

void setup() {
  Serial.begin(115200);                           //Begin Serial Monitor
  while (!Serial);                                //Wait for the Serial Monitor

  RS485.begin(BAUDRATE);                          //Begin RS485 with baurate = BAUDRATE (115200)
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);    //Set Weidos RS485 pins.

  
  RS485.receive();    // enable reception, can be disabled with: RS485.noReceive();
}

void loop() {
  if (RS485.available()) {          //If there is data in the RS485 interface:
    Serial.write(RS485.read());     //Read from the RS485 and print it to the Serial Monitor.
  }
}
