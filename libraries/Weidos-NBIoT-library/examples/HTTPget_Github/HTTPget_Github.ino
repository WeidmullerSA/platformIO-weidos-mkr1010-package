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
  HTTP GET example using NB client with ArduinoHttpClient library
  Connects to Github server once every five seconds, sends a GET request.
*/

//Libraries
#include <ArduinoHttpClient.h>
#include <MKRNB.h>

//NB Credentials
const char PINNUMBER[] = "";
const char APN[] = "wlapn.com";
const char USERNAME[] = "WLTRIALS";
const char PASSWORD[] = "WLTRIALS";

//Initialize the library instance
NB nbAccess (true); //Show AT Commands in Serial Monitor
//NB nbAccess;      //Hide AT Commands in Serial Monitor

//Initialize clients (NB-IoT and HTTP)
NBSSLClient NBclient;
char serverAddress[] = "raw.githubusercontent.com";  // server address
char path[] = "/WeidmullerSA/Weidos-index/main/Weidos_httpServer_exampleContent.json";
int port = 443;
HttpClient httpClient = HttpClient(NBclient, serverAddress, port);

void setup() {
  
  //Start Serial Monitor
  Serial.begin(115200);

  //Wait until Serial Monitor is open to continue with the Setup program
  while (!Serial) {}

  Serial.println("Starting Arduino web client.");
  //Connection state
  boolean connected = false;

  //NB-IOT Connection
  // After starting the modem with NB.begin()
  // Attach to the NB network with the APN, login and password
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER, APN, USERNAME, PASSWORD) == NB_READY)) {
      connected = true;
      Serial.println("Connected to NarrowBand network");
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("You're connected to the NB-IOT network");
  Serial.println();
  
}


void loop() {
       
      Serial.println("Making GET request");      
      httpClient.get(path);
          
      //Read the status code and body of the response
      int statusCode = httpClient.responseStatusCode();
      String response = httpClient.responseBody();
    
      Serial.print("Status code: ");
      Serial.println(statusCode);
      Serial.print("Response: ");
      Serial.println(response);
      
      Serial.println("Wait five seconds");
      delay(5000);
  
}
