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
  Multifunction pins as Digital Inputs example

  Constantly reads value from all Multifunction pins and prints it to the 
  Serial Monitor. It also shows that one can use different namings for the
  Multifunction pins: 
  - Connector Numbers: pin41, pin42
  - Weidos pin names: MF_0, MF_1
  
  Multi Function Input values are:
    - RANGE: 0V-3.3V or 0V-5V (depending on the DIP switches configuration)
    
  DIP switch configuration:
        0V-3.3V:  SW1: 1=ON, 2=ON, 3=ON,     4=indiferent   SW2=indiferent
        0V-5V:    SW1: 1=OFF, 2=OFF, 3=OFF,  4=indiferent   SW2=indiferent
*/


void setup(){
  Serial.begin(115200);
  pinMode(pin41, INPUT);
  pinMode(pin42, INPUT);  
}

void loop() {
  Serial.println("Connector numbers:");
  Serial.print(digitalRead(pin41));
  Serial.print(" - ");
  Serial.println(digitalRead(pin42));
  delay(500);
  
  Serial.println("Weidos MF pin names:");
  Serial.print(digitalRead(MF_0));
  Serial.print(" - ");
  Serial.println(digitalRead(MF_1));
  delay(500);  
}
