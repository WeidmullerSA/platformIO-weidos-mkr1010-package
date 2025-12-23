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
  Analog Input pins as Digital Inputs example

  Constantly reads digital value from all Analog Input pins and prints them
  in the Serial Monitor. 
  Input range:
      - LOW: <3.3V  (Falling edge)
      - HIGH: >5V   (Rising edge)
      - RANGE: 0V-24V

  It also shows that one can use different namings for the
  Analog Input pins: 
  - Connector Numbers: pin15, pin16, pin17, pin18
  - Weidos pin names: ADI_0, ADI_1, ADI_2, ADI_3
*/

void setup(){
  Serial.begin(115200);
}


void loop() {
  int digitalValue;
  Serial.println("Weidos pin names");
  digitalValue = digitalRead(ADI_0);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(ADI_1);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(ADI_2);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(ADI_3);
  Serial.println(digitalValue);
  delay(500);

  Serial.println("Connector numbers");
  digitalValue = digitalRead(pin15);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(pin16);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(pin17);
  Serial.print(digitalValue);
  Serial.print(" --- ");
  digitalValue = digitalRead(pin18);
  Serial.println(digitalValue);
  delay(500);
}
