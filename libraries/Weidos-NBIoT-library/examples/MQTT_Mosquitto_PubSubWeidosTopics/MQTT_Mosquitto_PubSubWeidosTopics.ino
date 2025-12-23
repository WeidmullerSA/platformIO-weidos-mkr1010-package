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
  MQTT Publish Subscribe

  This example connects Weidos Device to Mosquitto MQTT Broker.
  Weidos Subsribes to 2 different topics (WeidosTopic1 and WeidosTopic2)
  Weidos Publishes to WeidsoTopic1 a message with a counter value. 

**/

//Libraries
#include <MKRNB.h>
#include <ArduinoMqttClient.h>

//NB Credentials
const char PINNUMBER[] = "";
const char APN[] = "wlapn.com";
const char USERNAME[] = "WLTRIALS";
const char PASSWORD[] = "WLTRIALS";

//Initialize the library instance
//NB nbAccess (true); //Show AT Commands in Serial Monitor
NB nbAccess;          //Hide AT Commands in Serial Monitor

//Initialize clients (NB-IoT and MQTT)
NBSSLClient client_nb;
MqttClient mqttClient(client_nb);

//MQTT Data
const char broker[] = "test.mosquitto.org";
int        port     = 8886;
const char topic[]  = "WeidosTopic1";
const char topic2[]  = "WeidosTopic2";

//Variables
const long interval = 10000;
unsigned long previousMillis = 0;
int count = 0;


void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  
  
  //NB-IOT Connection
  // After starting the modem with NB.begin()
  // Attach to the NB network with the APN, login and password
  boolean connected = false;
  Serial.println("Connecting to NB-IOT network");
  Serial.println();
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER, APN, USERNAME, PASSWORD) == NB_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("You're connected to the NB-IOT network");
  Serial.println();

  //MQTT Broker Connection
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  //Set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  //Subscribe to topics
  mqttClient.subscribe(topic);
  mqttClient.subscribe(topic2);

  //Unsubcribe from topic
  //mqttClient.unsubscribe(topic);

  Serial.print("Subscribed to topic 1: ");
  Serial.println(topic);
  Serial.print("Subscribed to topic 2: ");
  Serial.println(topic2);
 
}

void loop() {

  //Check MQTT incoming messages
    //Call poll() regularly to allow the library to receive MQTT messages and
    //Send MQTT keep alive which avoids being disconnected by the broker
    mqttClient.poll();

  //Publish to MQTT topic (every interval)
    unsigned long currentMillis = millis();  
      if (currentMillis - previousMillis >= interval) {
       //Save the last time a message was sent
       previousMillis = currentMillis;

       Serial.print("Sending message to: ");
       Serial.println(topic);
       Serial.print("Weidos message: ");
       Serial.println(count);

       //Send message, the Print interface can be used to set the message contents
       mqttClient.beginMessage(topic);
       mqttClient.print("Weidos message: ");
       mqttClient.print(count);
       mqttClient.endMessage();
       Serial.println();
       count++;
      }

  //Check MQTT connection   
      if (!mqttClient.connected()) {
       //Connect with MQTT Broker
        Serial.print("Not connected. Connecting...");    
        if (!mqttClient.connect(broker, port)) {
          Serial.print("MQTT connection failed! Error code = ");
          Serial.println(mqttClient.connectError());
        }
        else {
          //Subscribe to topics
          mqttClient.subscribe(topic);
          mqttClient.subscribe(topic2);     
        } 
      }  
}


void onMqttMessage(int messageSize) {
  //Received a message, print out the topic and contents
  Serial.println("New message received");
  Serial.print("Topic: ");
  Serial.print(mqttClient.messageTopic());
  Serial.print(" - Length: ");
  Serial.print(messageSize);
  Serial.println(" bytes");

  //Use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }  
  Serial.println();
  Serial.println();
}
