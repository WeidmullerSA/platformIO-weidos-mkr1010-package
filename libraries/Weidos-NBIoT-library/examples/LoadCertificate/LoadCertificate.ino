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
  NB Load Certificate to SARA R412

  This example Loads the Certificate intruduced in Cert.h file to SARA-R412 chip 
  it also shows the list of certificates to check it was loadad correctly. 

**/

//Libraries
#include <MKRNB.h>
#include "Cert.h"

//Initialize the library instance
NB nbAccess (true); //Show AT Commands in Serial Monitor
//NB nbAccess;      //Hide AT Commands in Serial Monitor

//Defines
#define LOG(x)  Serial.println(x)
String  response;
int     reps;
int     rest;
int     Buffer_size=420;
int     i;

void setup()
{

  //Delay of 10 sec to Open Serial Monitor
  delay(10000);
  
  //Start Serial Monitor
  Serial.begin(115200);

  //Wait until Serial Monitor is open to continue with the Setup program
  while (!Serial) {}

  //Begin Modem SARA-R412
  MODEM.begin();
  LOG("");
  
  reps = Cert_size / Buffer_size;
  rest = Cert_size % Buffer_size;

  //AT Command to Load Certificate to SARA-R412 Modem
  MODEM.sendf("AT+USECMNG=0,0,\"%s\",%d\r\n", Cert_name, Cert_size);
  
  if (MODEM.waitForPrompt() != 1) {
    //Failure
    LOG("Failure transfering Certificate to SARA-R412");
  }else{
    for(i=0;i<reps;i++){
       //Send Certificate content
       MODEM.write(Cert_data+i*Buffer_size, Buffer_size);
       delay(10);
    }
    MODEM.write(Cert_data+reps*Buffer_size, rest);    
    LOG("Certificate content sent to Modem succesfully");
    MODEM.waitForResponse(5000, &response);
    delay(2000);
  }  
}

void loop()
{ 
  
  LOG("");
  LOG("List all Certificates Stored in memory of SARA-R412 modem (max 15 certificates) \n"); 
  
  //AT Command to List all Certificates Stored in SARA-R412  
  MODEM.send("AT+USECMNG=3\r\n");
  MODEM.waitForResponse(5000, &response);
  Serial.println("");

  LOG("Change content in Cert.h to load new Certificate and Load this program again");

  while(1);
  
}
