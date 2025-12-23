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
  RS485 Send example

  This sketch periodically sends a string over the RS485 interface.
  
  DIP switches MUST be configured to use RS485:
  SW1: 4=ON 1,2,3=indifferent
  SW2: 1=OFF, 2=OFF, 3=ON, 4=ON

  To receive what it's being sent, example RS485_receive (File/Examples/RS485/RS485_receive) can be used in a second Weidos. Both Weidos'
  DIP switches MUST be configured to use RS485. Wire pin11 <-> pin11 and pin12 <-> pin12.

  WARNING!!! DIP switches must be configured to use RS485 prior to ANY WIRING with your device POWERED OFF.
  WARNING!!! Not following this instructions may damage your device.
  WARNING!!! Check User Manual for more information.
*/

#include <ArduinoRS485.h>

#define BAUDRATE 115200     //RS485 baudrate
int counter = 0;            

void setup() {
  RS485.begin(BAUDRATE);                          //Begin RS485 with baurate = BAUDRATE (115200)
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);    //Set Weidos RS485 pins.
}


void loop() {
  RS485.beginTransmission();
  RS485.print("Hello, Weidmuller here! ");
  RS485.println(counter);
  RS485.endTransmission();
  counter++;
  delay(1000);
}
