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
  Ethernet Static IP Configuration example

  Example that initializes Ethernet shield and connects to the network with Static IP.
  It also checks for the presence of the shield and if the Ethernet cable is
  connected. If properly configured, it periodically prints the IP address.  
 */

#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 110);       // user defined Static IP
IPAddress myDns(8, 8, 8, 8);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


void setup() { 
  Serial.begin(115200);   // begin Serial
  while(!Serial){}        // wait for the Serial to be opened.
  Serial.println("Trying to connect. It can take a while!");
  
  Ethernet.init(ETHERNET_CS);   // initialize Ethernet with Weidos' Ethernet Chips Select.
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  
  // check if Ethernet hardware is present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware!");
    while (true){}; //do nothing
  }
  else delay(2000);

  if (Ethernet.linkStatus() == LinkOFF) Serial.println("Ethernet cable is not connected.");
}



void loop() {
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());
  delay(3000); 
}
