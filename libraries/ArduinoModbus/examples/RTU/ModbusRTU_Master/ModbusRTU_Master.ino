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
  Modbus RTU Master example

  Example to configure a Modbus RTU Master.

  DIP switches MUST be configured to use RS485:
  SW1: 4=ON 1,2,3=indifferent
  SW2: 1=OFF, 2=OFF, 3=ON, 4=ON
  
  Modbus RTU Master configured with the following:
    - Baudrate: 19200
    - Data Structure: SERIAL_8E1. That is:
          - Data bits: 8
          - Parity: Even   
          - Stop bits: 1
  Available configurations are defined in file "HardwareSerial.h" (Arduino15/packages/weidmuller/hardware/samd/X.X.X/cores/weidmuller/api/HardwareSerial.h)

  Each 5 seconds it makes 4 requests:
    1- 3 consecutive COILS starting at address 700.
    2- 3 consectutive DISCRETE INPUTS starting at address 800.
    3- 3 consecutive HOLDING REGISTERS starting at address 900.
    4- 5 consecutive INPUT REGISTERS starting at address 1000.
  
  This example can be used with a second Weidos with example: ModbusRTU_Slave (File/Examples/ArduinoModbus/RTU/ModbusRTU_Slave)
  Change DIP switches to the RS485 configuration, wire pin11 <-> pin11 and pin12 <-> pin12 and upload ModbusRTU_Slave example to the second Weidos.

  WARNING!!! DIP switches must be configured to use RS485 prior to ANY WIRING with your device POWERED OFF.
  WARNING!!! Not following this instructions may damage your device.
  WARNING!!! Check User Manual for more information.
*/


#include <ArduinoRS485.h>
#include <ModbusRTUClient.h>


#define SLAVE_ADDRESS   1                 //Modbus Slave address to request data from.
#define BAUDRATE        19200             //Baudrate


#define FIRST_COIL                700     //First Coil's address.
#define FIRST_DISCRETE_INPUT      800     //First Discrete Input's address.
#define FIRST_HOLDING_REGISTER    900     //First Holding Register's address.
#define FIRST_INPUT_REGISTER      1000    //First Input Register's address. 


#define NUM_COILS                 3       //Number of consecutive Coils to read.
#define NUM_DISCRETE_INPUTS       3       //Number of consecutive Discrete Inputs to read.
#define NUM_HOLDINGS_REGISTERS    3       //Number of consecutive Holding Registers to read.
#define NUM_INPUT_REGISTERS       5       //Number of consecutive Input Registers to read.

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);        //Set Weidos RS485 pins.
  if(!ModbusRTUClient.begin(BAUDRATE, SERIAL_8E1)){   //Modbus client configured as 8 data bits, Even parity and 1 stop bit (SERIAL_8E1).
    Serial.println("Client not initialized!");    
  }
  else Serial.println("Client successfully initialized");
}

void loop() {
  delay(5000);

  
  Serial.println("Reading Coils:");
  ModbusRTUClient.requestFrom(SLAVE_ADDRESS, COILS, FIRST_COIL, NUM_COILS);
  for(int i = 0; i<NUM_COILS; i++){
    long data = ModbusRTUClient.read();
    Serial.println(data);
  }
  
  Serial.println("Reading Discrete Inputs:");
  ModbusRTUClient.requestFrom(SLAVE_ADDRESS, DISCRETE_INPUTS, FIRST_DISCRETE_INPUT, NUM_DISCRETE_INPUTS);
  for(int i = 0; i<NUM_DISCRETE_INPUTS; i++){
    long data = ModbusRTUClient.read();
    Serial.println(data);
  }
  
  Serial.println("Reading Holding Registers:");
  ModbusRTUClient.requestFrom(SLAVE_ADDRESS, HOLDING_REGISTERS, FIRST_HOLDING_REGISTER, NUM_HOLDINGS_REGISTERS);
  for(int i = 0; i<NUM_HOLDINGS_REGISTERS; i++){
    long data = ModbusRTUClient.read();
    Serial.println(data);
  }

  Serial.println("Reading Input Registers:");
  ModbusRTUClient.requestFrom(SLAVE_ADDRESS, INPUT_REGISTERS, FIRST_INPUT_REGISTER, NUM_INPUT_REGISTERS);
  for(int i = 0; i<NUM_INPUT_REGISTERS; i++){
    long data = ModbusRTUClient.read();
    Serial.println(data);
  }

  Serial.println();
  Serial.println();
  
}
