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
 LoRa Rx example.

 Receive data sent via LoRa without the need of a gateway, App Key, App EUI or other parameters
 since it does not uses LoRaWAN protocol, only the physical layer of LoRa.

 Note: use LoRa_Tx example with a second Weidos to see that it receives a known message.
*/

#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Welcome");
  LoRa.begin();
}


void loop() {
  String data = LoRa.radioRx();
  if(data.length()>0) Serial.println(data);
}
