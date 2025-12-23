/**
Copyright (C) 2024 Weidmüller SA. All rights reserved.
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
**/

/**
  NB Network Connect

  This example connects the Weidos Device to Narrow Band IoT Network. 

**/

//Libraries
#include <MKRNB.h>

//NB Credentials
const char PINNUMBER[] = "";
const char APN[] = "wlapn.com";
const char USERNAME[] = "WLTRIALS";
const char PASSWORD[] = "WLTRIALS";

//Initialize the library instance
NB nbAccess (true); //Show AT Commands in Serial Monitor
//NB nbAccess;      //Hide AT Commands in Serial Monitor

void setup(){

  //Start Serial Monitor
  Serial.begin(115200);

  //Wait until Serial Monitor is open to continue with the Setup program
  while (!Serial) {}

  Serial.println("Connecting to NB-IoT Network...");
  
  //Define flag for connection state
  boolean connected = false;

  //Connect to the NB-IOT network with the APN, login and password
  while (!connected)
  {
    if (nbAccess.begin(PINNUMBER, APN, USERNAME, PASSWORD) == NB_READY) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("Connected to NB-IOT network!");
}

void loop()
{

}
