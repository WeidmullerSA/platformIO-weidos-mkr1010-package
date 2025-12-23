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
  Send AT commands to SARA-R412 Modem with Serial Monitor

  This example allow user to send AT commands to NB-IOT Modem.
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

//Define Variables
#define LOG(x) Serial.println(x)
void getString(String& string);
uint8_t waitForOk(void);
#define BUFFER_SIZE 200

void setup() {
  
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


void loop() { 
  
  LOG("Enter AT command");
  String atCommand;
  getString(atCommand);
  char charArray[BUFFER_SIZE];
  int arrayLength = atCommand.length();
  
  atCommand.toCharArray(charArray, BUFFER_SIZE);
  charArray[arrayLength-1] = '\r';
  charArray[arrayLength] = '\n';
  charArray[arrayLength+1] = '\0';
  
  Serial.print("Command: ");
  Serial.write(charArray);
  MODEM.send(charArray);
  Serial.println("Response: ");
  String response;
  MODEM.waitForResponse(5000, &response);
  
}


void getString(String& string){
  bool stringRead = false;
  while(!stringRead){
    if(Serial.available()){
      string = Serial.readString();
      stringRead = true;
    }
  }
}
