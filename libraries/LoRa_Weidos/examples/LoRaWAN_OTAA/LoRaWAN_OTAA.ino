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
 LoRaWAN OTAA example.

 LoRaWAN OTAA example to join and send data to a gateway. Sending data can be done with and without confirmation. Downlink messages are also handled.  
 Note: This example requires a Gateway. Use "LoRa Radio Send" and "LoRa Radio Receive" examples to test LoRa without requiring a Gateway. 

 To use this example, create an Application to get its "Application EUI" and "Application Key". Register your "Device EUI" to your Application and 
 ensure you have good coverage with the Gateway.  
 */


#include <LoRa.h>

  String appEUI = "763c25451c164735";                       //Example App EUI. It must be changed.
  String appKey = "e6b79cf26ac4d5e2cc97d356bd611fe7";       //Example App Key. It must be changed.
  

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Welcome!");

  LoRa.begin();                                             //Initialize LoRa chip.
  String devEUI = LoRa.hweui();                             //Get LoRa's chip globally unique Device EUI.
  Serial.print("Using OTAA, register this deviceEUI: ");
  Serial.println(devEUI);

  Serial.println("Trying to join via OTAA...");
  bool joined = LoRa.initOTAA(appEUI, appKey, devEUI);      //Join a Network via LoRaWAN OTAA. devEUI can be user defined.
  //bool initLoRa = LoRa.initOTAA(appEUI, appKey);          //If no devEUI argument passed. LoRa library automatically gets device's unique Device EUI.
  
  if(joined){
    Serial.println("Successfully joined!"); 
  }else{
    Serial.println("Unable to join!");
    Serial.println("1- Verify your Application EUI, Application Key");
    Serial.println("2- Verify your Device EUI is registered in your Application");
    Serial.println("3- Check network's coverage");
    Serial.println("Restart your device to try again");
    while(true){}
  }
}


void loop() {
  Serial.println("Sending a message...");
  TX_RETURN_TYPE  messageSent = LoRa.send("Hello world. Weidos here!", true);     //Send message with confirmation (true) and save response into a flag to check if it was successfully sent.
  if(messageSent == TX_SUCCESS) Serial.println("Message successfully sent!");     
  else if(messageSent == TX_WITH_RX){                                             //If there is a downlink message
    Serial.println("Message successfully sent!");
    Serial.print("It contains Downlink message: ");
    Serial.println(LoRa.getRx());
  }else{
    Serial.println("Message NOT successfully sent!");
  }
  delay(30000);
}
