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
  Digital Inputs example

  Constantly reads value from all Digital Inputs and prints it to the 
  Serial Monitor. It also shows that one can use different namings for the
  Digital Input pins: 
  - Connector Numbers: pin25, pin26, pin27, pin28
  - Weidos pin names: DI_4, DI_5, DI_6, DI_7
  
  Digital Input values are:
    - LOW: <3.3V  (Falling edge)
    - HIGH: >5V   (Rising edge)
    - RANGE: 0V-24V
*/


void setup(){
  Serial.begin(115200);  
}

void loop() {
  Serial.println("Connector numbers:");
  Serial.print(digitalRead(pin25));
  Serial.print(" - ");
  Serial.print(digitalRead(pin26));
  Serial.print(" - ");
  Serial.print(digitalRead(pin27));
  Serial.print(" - ");
  Serial.println(digitalRead(pin28));
  delay(500);
  
  Serial.println("Weidos DI pin names:");
  Serial.print(digitalRead(DI_4));
  Serial.print(" - ");
  Serial.print(digitalRead(DI_5));
  Serial.print(" - ");
  Serial.print(digitalRead(DI_6));
  Serial.print(" - ");
  Serial.println(digitalRead(DI_7));
  delay(500);  
}
