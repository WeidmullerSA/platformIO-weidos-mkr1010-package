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

/**
  Multifunction pins as Digital Outputs example

  Turns ON/OFF each multifunction pin sequentially.
  To check outputs use a multimeter or an LED.
  
  It also shows that one can use different naming for the
  Multifunction pins: 
  - Connector Numbers: pin41, pin42
  - Weidos pin names: MF_0, MF_1

  OUTPUT RANGE:
      LOW: GND
      HIGH: 3.3V or 5V (depending on the DIP switches configuration)

  DIP switch configuration:
        0V-3.3V:  SW1: 1=ON, 2=ON, 3=ON,     4=indiferent   SW2=indiferent
        0V-5V:    SW1: 1=OFF, 2=OFF, 3=OFF,  4=indiferent   SW2=indiferent
 */


void setup(){
  Serial.begin(115200);
  pinMode(pin41, OUTPUT);
  pinMode(pin42, OUTPUT);
}


void loop() {
  
  //Turn on LED's using connector pin number (pinXX)
  digitalWrite((pin41), HIGH);
  delay(2000);
  digitalWrite((pin42), HIGH);
  delay(2000);
  
  //Turn off LED's using Weidos pin names (MF_X)
  digitalWrite((MF_0), LOW);
  delay(2000);
  digitalWrite((MF_1), LOW);
  delay(2000);
}
