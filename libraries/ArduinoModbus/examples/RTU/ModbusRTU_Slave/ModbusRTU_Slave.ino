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
  Modbus RTU Slave example

  Example that shows how to set up a Modbus RTU Slave with Coils,
  Discrete Inputs, Holding and Input Registers.
   
  DIP switches must be configured to use RS485:
  SW1: 4=ON 1,2,3=indifferent
  SW2: 1=OFF, 2=OFF, 3=ON, 4=ON

  Slave is configured with the following:
    - Slave address: 1
    - Baudrate: 19200
    - Data Structure: 8 data bits, Even parity and 1 stop bits (SERIAL_8E1). Available configurations are defined in
                      file "HardwareSerial.h" (Arduino15/packages/weidmuller/hardware/samd/X.X.X/cores/weidmuller/api/HardwareSerial.h 
    - Data Structure: SERIAL_8E1. That is:
          - Data bits: 8
          - Parity: Even   
          - Stop bits: 1
   Available configurations are defined in file "HardwareSerial.h" (Arduino15/packages/weidmuller/hardware/samd/X.X.X/cores/weidmuller/api/HardwareSerial.h) 

    - Coils: 3 consecutive coils starting at address 700. Its values are: 1,0,0
    - Discrete Inputs: 3 consecutive discrete inputs starting at address 800. Its values are: 0,1,0
    - Holding Registers: 3 consecutive holding registers starting at address 900. Its values are: 777,888,999
    - Input Registers: 5 consecutive input registers starting at address 1000. Its values are: 100,1020,4020,23,1314


  In order to request data from this server, a second Weidos can be used with the example: ModbusRTU_Master (File/Examples/ArduinoModbus/RTU/ModbusRTU_Master)
  Change DIP switches to the RS485 configuration, wire pin11 <-> pin11 and pin12 <-> pin12 and upload ModbusRTU_Master example to the second Weidos. 

  WARNING!!! DIP switches must be configured to use RS485 prior to any wiring with your device powered off.
  WARNING!!! Not following this instructions may damage your device.
  WARNING!!! Check User Manual for more information.
*/
 
#include <ModbusRTUServer.h>


uint16_t inputRegisterValues[] = {100, 1020, 4020, 23, 1314};         //Array with values that will be stored in the Input Registers.
uint8_t discreteInputValues[] = {0,1,0};                              //Array with values that will be stored in the Discrete Inputs.
const unsigned long baudrate = 19200;                                 //Baudrate
const int slaveAddress = 1;                                           //Modbus slave address


void setup() {
  ModbusRTUServer.begin(RS485, slaveAddress, baudrate, SERIAL_8E1);   //SERIAL_8E1 => 8 data bits, Even parity and 1 stop bit. Available configurations are defined in
                                                                      //file "HardwareSerial.h" (Arduino15/packages/weidmuller/hardware/samd/X.X.X/cores/weidmuller/api/HardwareSerial.h
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);                        //Set Weidos RS485 pins.
  RS485.setDelays(70, 70);
  RS485.setTimeout(100);

  ModbusRTUServer.configureCoils(700, 3);                             //Create 3 coils with address starting at 700.
  ModbusRTUServer.coilWrite(700, 1);                                  //Set value = 1 for coil with address 700.                      
  ModbusRTUServer.coilWrite(701, 0);                                  //Set value = 0 for coil with address 701. 
  ModbusRTUServer.coilWrite(702, 0);                                  //Set value = 0 for coil with address 702.

 
  ModbusRTUServer.configureDiscreteInputs(800, 3);                    //Create 3 discrete inputs with address starting at 800.
  ModbusRTUServer.writeDiscreteInputs(800, discreteInputValues, 3);   //Set discrete inputs accorgint to the array "discreteInputValues". Values = 0,1,0
                                                                      //Alternatively one can use discreteInputWrite() to set discrete inputs one by one.

  ModbusRTUServer.configureHoldingRegisters(900, 3);                  //Create 3 holding registers with address starting at 900.
  ModbusRTUServer.holdingRegisterWrite(900, 777);                     //Set value = 777 for holding register with address 900.
  ModbusRTUServer.holdingRegisterWrite(901, 888);                     //Set value = 888 for holding register with address 901.
  ModbusRTUServer.holdingRegisterWrite(902, 999);                     //Set value = 999 for holding register with address 902.

  ModbusRTUServer.configureInputRegisters(1000, 5);                   //Create 5 input registers with address starting at 1000.
  ModbusRTUServer.writeInputRegisters(1000, inputRegisterValues, 5);  //Set input registers according to the array "inputRegisterValues". Values = 100, 1020, 4020, 23, 1314
                                                                      //Alternatively one can use inputRegisterWrite() to set input registers one by one. 
}


void loop() {
  ModbusRTUServer.poll();         //Frequentlly poll to check if there are any requests and to answer them when there are.
}
