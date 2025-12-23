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
  I2C Slave Receive example

  This sketch shows how to set up a Weidos as an I2C Slave device and receive data from
  an I2C Master device. For any byte received, it prints its value in the Serial Monitor.
  
  Use a second Weidos with example I2C_master_send (File/Examples/I2C/I2C_master_send) in order to
  send data via I2C so it can be read by this example. Wire both Weidos' I2C SDA and SCL pins (pin61<->pin61
  and pin62<->pin62).
*/

#include <Wire.h>


//Function to be called whenever data is received.
//In this case, it reads all received data and prints it to the Serial Monitor.

void receiveEvent(int num){
  Serial.print("Number of received bytes: ");
  Serial.println(num);
 
  for(int i=0; i<num; i++){           //Alternatively, you can use:  while(Wire.available()){}
    Serial.print("Recieved byte: ");
    Serial.println(Wire.read());  
  }
}


#define SLAVE_ADDRS 0x55  //I2C slave address
void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Program up and running!");
  Serial.println("Every byte of data received via I2C will be printed in the Serial Monitor");
  Wire.begin(SLAVE_ADDRS);        //Begin Wire object with the Slave Address as an argument so I2C Slave is initialized.
  Wire.onReceive(receiveEvent);   //Attach function to be called whenever data is recevied (function defined above).
}

void loop() {
}
