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
  Analog Output example

  For the Analog Output pin (AO_0) it writes an analog value that goes from 0V to 10V over time.
  Once it reaches its maximum value (10V), after 5 seconds it starts again from 0V.
  Analog Output resolution is 10-bits (0-1023). 
  It also shows different namings for the Analog Output pin: 
  - Connector Number: pin45
  - Weidos pin name: AO_0
*/

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Connector number");
  for(uint16_t i=0; i<1024;i++)
  {
    delay(15);
    analogWrite(pin45, i);
    Serial.println(i);
  } 
  delay(5000);
  
  Serial.println("Weidos pin name");
  for(uint16_t i=0; i<1024;i++)
  {
    delay(15);
    analogWrite(AO_0, i);
    Serial.println(i);
  }
  delay(5000);
}
