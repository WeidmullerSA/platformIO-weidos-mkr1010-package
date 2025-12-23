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


/*
  Modbus TCP Slave example

  Example that shows how to set up a Modbus TCP Slave with Coils,
  Discrete Inputs, Holding and Input Registers.

    - Coils: 3 consecutive coils starting at address 700. Its values are: 1,0,0
    - Discrete Inputs: 3 consecutive discrete inputs starting at address 800. Its values are: 0,1,0
    - Holding Registers: 3 consecutive holding registers starting at address 900. Its values are: 777,888,999
    - Input Registers: 5 consecutive input registers starting at address 1000. Its values are: 100,1020,4020,23,1314
*/

#include <Ethernet.h>
#include <ArduinoModbus.h>
 
EthernetServer server(502);
ModbusTCPServer modbusTCPServer;

//Ethernet data
IPAddress ip(192, 168, 0, 20);       //User defined Static IP
IPAddress myDns(8, 8, 8, 8);
IPAddress gateway(192, 168, 0, 10);  //User difined Gateway
IPAddress subnet(255, 255, 255, 0);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //MAC address of your device

uint16_t inputRegisterValues[] = {100, 1020, 4020, 23, 1314};         //Array with values that will be written in the Input Registers.
uint8_t discreteInputValues[] = {0,1,0};                              //Array with values that will be written in the Discrete Inputs.

void setup() {
  
  Serial.begin(115200);

  Ethernet.init(ETHERNET_CS);
  if (Ethernet.linkStatus() == LinkOFF) Serial.println("Ethernet Cable is not connected");
  
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  server.begin();
  
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }
    
  modbusTCPServer.configureCoils(700, 3);                             //Create 3 coils with address starting at 700.
  modbusTCPServer.coilWrite(700, 1);                                  //Set value = 1 for coil with address 700.                      
  modbusTCPServer.coilWrite(701, 0);                                  //Set value = 0 for coil with address 701. 
  modbusTCPServer.coilWrite(702, 0);                                  //Set value = 0 for coil with address 702.
  
 
  modbusTCPServer.configureDiscreteInputs(800, 3);                    //Create 3 discrete inputs with address starting at 800.
  modbusTCPServer.writeDiscreteInputs(800, discreteInputValues, 3);   //Set discrete inputs accorgint to the array "discreteInputValues". Values = 0,1,0
                                                                      //Alternatively one can use discreteInputWrite() to set discrete inputs one by one.
                                                                      
  modbusTCPServer.configureHoldingRegisters(900, 3);                  //Create 3 holding registers with address starting at 900.
  modbusTCPServer.holdingRegisterWrite(900, 777);                     //Set value = 777 for holding register with address 900.
  modbusTCPServer.holdingRegisterWrite(901, 888);                     //Set value = 888 for holding register with address 901.
  modbusTCPServer.holdingRegisterWrite(902, 999);                     //Set value = 999 for holding register with address 902.
  

  modbusTCPServer.configureInputRegisters(1000, 5);                   //Create 5 input registers with address starting at 1000.
  modbusTCPServer.writeInputRegisters(1000, inputRegisterValues, 5);  //Set input registers according to the array "inputRegisterValues". Values = 100, 1020, 4020, 23, 1314
                                                                      //Alternatively one can use inputRegisterWrite() to set input registers one by one. 
}


void loop() {

  EthernetClient client = server.available();
  if (client) {
    modbusTCPServer.accept(client);   //Let the Modbus TCP accept the connection
    while (client.connected()) {
      modbusTCPServer.poll();         //Frequentlly poll to check if there are any requests and to answer them when there are.
    }
  }

}
