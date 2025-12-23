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
  Modbus TCP Master example

  Example to configure a Modbus TCP Master.
*/

#include <Ethernet.h>

#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

#define SLAVE_ADDRESS 1

#define FIRST_COIL                700     //First Coil's address.
#define FIRST_DISCRETE_INPUT      800     //First Discrete Input's address.
#define FIRST_HOLDING_REGISTER    900     //First Holding Register's address.
#define FIRST_INPUT_REGISTER      1000    //First Input Register's address. 


#define NUM_COILS                 3       //Number of consecutive Coils to read.
#define NUM_DISCRETE_INPUTS       3       //Number of consecutive Discrete Inputs to read.
#define NUM_HOLDINGS_REGISTERS    3       //Number of consecutive Holding Registers to read.
#define NUM_INPUT_REGISTERS       5       //Number of consecutive Input Registers to read.


// Enter a MAC address for your device ethernet port.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE9 };
IPAddress ip(192, 168, 0, 10);

EthernetClient ethClient;
ModbusTCPClient modbusTCPClient(ethClient);

IPAddress server(192, 168, 0, 20); // update with the IP Address of your Modbus server

void setup() {
  Serial.begin(115200);

  Ethernet.init(ETHERNET_CS);
  if (Ethernet.linkStatus() == LinkOFF) Serial.println("Ethernet Cable is not connected");
  
  Ethernet.begin(mac, ip);  
  
}

uint16_t counter = 0;
bool toggle = true;

void loop() {    
  
  if (!modbusTCPClient.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    
    if (!modbusTCPClient.begin(server, 502)) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } else {
    Serial.println("Reading Coils:");
    modbusTCPClient.requestFrom(SLAVE_ADDRESS, COILS, FIRST_COIL, NUM_COILS);
    for(int i = 0; i<NUM_COILS; i++){
      long data = modbusTCPClient.read();
      Serial.println(data);
    }
    
    Serial.println("Reading Discrete Inputs:");
    modbusTCPClient.requestFrom(SLAVE_ADDRESS, DISCRETE_INPUTS, FIRST_DISCRETE_INPUT, NUM_DISCRETE_INPUTS);
    for(int i = 0; i<NUM_DISCRETE_INPUTS; i++){
      long data = modbusTCPClient.read();
      Serial.println(data);
    }
    
    Serial.println("Reading Holding Registers:");
    modbusTCPClient.requestFrom(SLAVE_ADDRESS, HOLDING_REGISTERS, FIRST_HOLDING_REGISTER, NUM_HOLDINGS_REGISTERS);
    for(int i = 0; i<NUM_HOLDINGS_REGISTERS; i++){
      long data = modbusTCPClient.read();
      Serial.println(data);
    }
  
    Serial.println("Reading Input Registers:");
    modbusTCPClient.requestFrom(SLAVE_ADDRESS, INPUT_REGISTERS, FIRST_INPUT_REGISTER, NUM_INPUT_REGISTERS);
    for(int i = 0; i<NUM_INPUT_REGISTERS; i++){
      long data = modbusTCPClient.read();
      Serial.println(data);
    }

    Serial.println("Write counter into holding register with address 900");
    modbusTCPClient.holdingRegisterWrite(900, ++counter);
    Serial.print("Written value in holding register: ");
    Serial.println(counter);
    
    Serial.println("Write boolean into coil with address 700");
    toggle = !toggle;
    modbusTCPClient.coilWrite(700, toggle);
    Serial.print("Written value in coil: ");
    Serial.println(toggle);
    Serial.println("-------------------------------");
    Serial.println();
    delay(5000);
  
  }  
  
}
