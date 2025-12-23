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
  Digital Outputs example

  Turns ON/OFF each digital output sequentially.
  To check how it works, take a look on Weidos' LEDs.
  OUTPUT RANGE:
      LOW: GND
      HIGH: (Vin - 1V) (Vin = Weidos power supply voltage)

  It also shows that one can use different naming for the
  Digital Output pins: 
  - Connector Numbers: pin55, pin56, pin57, pin58
  - Weidos pin names: DO_0, DO_1, DO_2, DO_3
 */


void setup(){}


void loop() {
  
  //Turn on LED's using connector pin number (pinXX)
  digitalWrite((pin55), HIGH);
  delay(500);
  digitalWrite((pin56), HIGH);
  delay(500);
  digitalWrite((pin57), HIGH);
  delay(500);
  digitalWrite((pin58), HIGH);
  delay(500);

  //Turn off LED's using Weidos pin names (DO_X)
  digitalWrite((DO_0), LOW);
  delay(500);
  digitalWrite((DO_1), LOW);
  delay(500);
  digitalWrite((DO_2), LOW);
  delay(500);
  digitalWrite((DO_3), LOW);
  delay(500);
}
