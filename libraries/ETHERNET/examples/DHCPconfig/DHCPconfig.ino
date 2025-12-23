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
  Ethernet DHCP Configuration example

  Example that initializes Ethernet shield and connects to the network via DHCP.
  It also checks for the presence of the shield and if the Ethernet cable is
  connected. If properly configured, it periodically prints the assigned IP address.  
 */


#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};      //User defined MAC


void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Trying to connect. It can take a while!");
  
  Ethernet.init(ETHERNET_CS);  // initialize Ethernet with Weidos' Ethernet Chips Select.
  if (Ethernet.begin(mac) == 0) Serial.println("Failed to configure Ethernet using DHCP");
  else Serial.println("DHCP set correctly.");

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware!");
    while(1);
  }
  else delay(2000);
  
  if (Ethernet.linkStatus() == LinkOFF) Serial.println("Ethernet cable is not connected.");
  
  Serial.print("Assigned IP address: ");
  Serial.println(Ethernet.localIP());
  
  byte macBuffer[6];  // create a buffer to hold the MAC address
  Ethernet.MACAddress(macBuffer); // fill the buffer
  Serial.print("MAC address: ");
  for (byte octet = 0; octet < 6; octet++) {
    Serial.print(macBuffer[octet], HEX);
    if (octet < 5) {
      Serial.print('-');
    }
  }
  Serial.println();
}


void loop() {
  Serial.print("Assigned IP address: ");
  Serial.println(Ethernet.localIP());
  delay(3000);
  
}
