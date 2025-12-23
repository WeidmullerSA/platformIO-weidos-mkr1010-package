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
 LoRa Tx example.

 Transmit data via LoRa without the need of a gateway, App Key, App EUI or other parameters
 since it does not uses LoRaWAN protocol, only the physical layer of LoRa.

 Note 1: Only hexadecimal characters can be sent (0123456789ABCDEF, non-case sensitive). 
 Note 2: use LoRa_Rx example with a second Weidos to check that the message is being sent.
*/

#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  LoRa.begin();
}

void loop() {
  String data = "0123456789ABCDEF";
  Serial.println("Sending data");
  RadioError error = LoRa.radioTx(data);
  
  if(!error) Serial.println("Data sent successfully!");
  if(error == RADIO_INVALID_PARAM){
    Serial.println("Error: Invalid parameter!");
    Serial.println("Allowed characters in the String data are: 0123456789ABCDEF (non-case sensitive)");
  }
  if(error == RADIO_BUSY) Serial.println("Error: Radio busy!");
  if(error == RADIO_TIMEOUT) Serial.println("Error: Radio Timeout!");
  
  Serial.println();
  delay(5000);
}
