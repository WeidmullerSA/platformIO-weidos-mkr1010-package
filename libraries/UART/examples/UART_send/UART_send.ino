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
  UART Send example

  This sketch periodically sends data over the UART interface.
  
  DIP switches MUST be configured to use UART:
  SW1: 4=OFF 1,2,3=indifferent
  SW2: 1=ON, 2=ON, 3=OFF, 4=OFF

  To receive what it's being sent, example UART_receive (File/Examples/UART/UART_receive) can be used in a second Weidos. Both Weidos'
  DIP switches MUST be configured to use UART. Wire pin11 <-> pin12 and pin12 <-> pin11.

  WARNING!!! DIP switches must be configured to use UART prior to ANY WIRING with your device POWERED OFF.
  WARNING!!! Not following this instructions may damage your device.
  WARNING!!! Check User Manual for more information.
*/


void setup() {
  UART.begin(115200);
}

uint8_t data[10] = {0,1,2,3,4,5,6,7,8,9};

void loop() {
  for(int i = 0; i<10; i++){
    UART.write(data[i]);
  }
  delay(5000);
}
