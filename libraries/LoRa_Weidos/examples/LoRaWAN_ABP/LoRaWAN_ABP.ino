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

 LoRaWAN ABP example.

 LoRaWAN ABP example to join and send data to a gateway. Sending data can be done with and without confirmation. Downlink messages are also handled.  
 Note: This example requires a Gateway. Use "LoRa Radio Send" and "LoRa Radio Receive" examples to test LoRa without requiring a Gateway. 

 To use this example, create an Application and register your device to get its "Application Session Key" and "Network Session Key". Register your "Device Address" to your Application and 
 ensure you have good coverage with the Gateway. 
 */


#include <LoRa.h>
String devAddress = "0203FFEC";                           //User defined Device Address. It must be registered in your Application.
String appSKey = "f3754aa07669e46ef76ea10123a6dd24";      //Example App Session Key. It must be changed.
String ntwSKey = "cda70f941e895e470ba9d61f4b14879d";      //Example Network Session Key. It must be changed.


void setup() {
  Serial.begin(115200);
  while(!Serial){}

  LoRa.begin();                                             //Initialize LoRa chip.

  Serial.println("Trying to join via ABP...");
  bool joined = LoRa.initABP(devAddress, appSKey, ntwSKey);    //Join a Network via LoRaWAN ABP.
  
  if(joined){
    Serial.println("Successfully joined!");
  }else{
    Serial.println("Unable to join!");
    Serial.println("1- Verify your Application Key and Network Key");
    Serial.println("2- Verify your Device Address is registered to your Application");
    Serial.println("3- Check network's coverage");
    Serial.println("Restart your device to try again");
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
