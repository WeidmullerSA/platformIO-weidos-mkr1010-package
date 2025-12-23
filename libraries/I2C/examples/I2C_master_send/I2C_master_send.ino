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
  I2C Master Send example

  This sketch shows how to set up a Weidos as an I2C Master device and send data to an I2C Slave device.
  
  Use a second Weidos to run example I2C_slave_receive (File/Examples/I2C/I2C_slave_receive) in order to
  read data sent by this example. Wire both Weidos' I2C SDA and SCL pins (pin61<->pin61 and pin62<->pin62).
*/

#include <Wire.h>
#define SLAVE_ADDRS 0x55

void setup() {
  Wire.begin();     //Initialize Wire object with no argument so an I2C master is configured.
}

void loop() {
  delay(3000);
  Wire.beginTransmission(SLAVE_ADDRS);     //Begin transmision with the slave device with address = SLAVE_ADDRS (0x55)
  Wire.write(2);    //Data to send
  Wire.write(8);    //Data to send
  Wire.write(100);  //Data to send
  Wire.write(23);
  //Add any Wire.write() and it will be sent and received by the IC2_slave_receive example.
  Wire.endTransmission();
}
