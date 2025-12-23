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
  NB List and Delete Certificates

  This example prints the list of Certificates stored in SARA-R412 chip 
  and allow to send via Serial Monitor the name of the Certificate to delete. 

**/

//Libraries
#include <MKRNB.h>

//Initialize the library instance
NB nbAccess (true); //Show AT Commands in Serial Monitor
//NB nbAccess;      //Hide AT Commands in Serial Monitor

//Defines
#define BUFFER_SIZE 1000
#define LOG(x) Serial.println(x)
void getString(String& string);
char charArray[BUFFER_SIZE];
int arrayLength;
String certificateToDelete;
String atCommand;
String response;


void setup() {

  //Start Serial Monitor
  Serial.begin(115200);

  //Wait until Serial Monitor is open to continue with the Setup program
  while (!Serial) {}

  LOG("Welcome");
  LOG("");
  //Begin Modem SARA-R412
  MODEM.begin();
  LOG("");

  //AT Command to List all Certificates Stored in SARA-R412
  MODEM.send("AT+USECMNG=3\r\n");
  MODEM.waitForResponse(5000, &response); //Timeout of 5000ms to wait response from Modem SARA-R412
  Serial.println("");
  
}

void loop() { 
  
  LOG("To delete a cetificate, enter its internal name, with the \"\"");
    
  //Read Serial Monitor input
  getString(certificateToDelete);

  //AT Command to Delete desired certificate
  atCommand = "AT+USECMNG=2,0,";
  atCommand.concat(certificateToDelete);  
  arrayLength = atCommand.length();  
  atCommand.toCharArray(charArray, BUFFER_SIZE);
  charArray[arrayLength-1] = '\r';
  charArray[arrayLength] = '\n';
  charArray[arrayLength+1] = '\0';
  MODEM.send(charArray);
  Serial.println("");
  MODEM.waitForResponse(5000, &response);
  Serial.println("");
  
  //List Certificates again to check it was deleted
  MODEM.send("AT+USECMNG=3\r\n");
  MODEM.waitForResponse(5000, &response);
  Serial.println("");
  
}


//Read String from Serial Monitor
void getString(String& string){
  bool stringRead = false;
  while(!stringRead){
    if(Serial.available()){
      string = Serial.readString();
      stringRead = true;
    }
  }
}
