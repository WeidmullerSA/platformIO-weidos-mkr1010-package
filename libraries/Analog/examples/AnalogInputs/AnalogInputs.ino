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
  Analog Inputs example

  Constantly reads value from all Analog Inputs and prints it to the 
  Serial Monitor.
  Input Range:  0V - 10V
  Resolution:   12-bits (0 - 4095)
  
  It also shows that one can use different naming for the Analog Inputs: 
  - Connector Numbers: pin15, pin16, pin17, pin18
  - Weidos pin names: ADI_0, ADI_1, ADI_2, ADI_3
*/


void setup() {
Serial.begin(115200);
}


void loop() {
  int analogValue;
  Serial.println("Weidos pin names");
  analogValue = analogRead(ADI_0);
  Serial.print(analogValue);              //Digital value (0-4095)
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);   //Analog value (0-10V)
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(ADI_1);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(ADI_2);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(ADI_3);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.println("V)");
  delay(100);

  Serial.println("Connector numbers");
  analogValue = analogRead(pin15);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(pin16);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(pin17);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.print("V)  -  ");
  delay(100);
  
  analogValue = analogRead(pin18);
  Serial.print(analogValue);
  Serial.print(" (");
  Serial.print(analogValue*10.0f/4095);
  Serial.println("V)");
  delay(100);
}
