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


#include <Wire.h>
#include "BR24T512.h"


BR24T512::BR24T512(){};

void BR24T512::begin(uint8_t i2c_addr, TwoWire* wire){
    this->i2c_addr = i2c_addr; 
	this->wire = wire;
	wire->begin();
};
uint8_t BR24T512::read(uint16_t index){
	uint8_t msb = highByte(index);
	uint8_t lsb = lowByte(index);
	wire->beginTransmission((uint8_t)i2c_addr);
	wire->write(msb);
	wire->write(lsb);
	wire->endTransmission(false);
	wire->requestFrom(i2c_addr, (uint8_t)1);
	uint8_t data = wire->read();
	return data;
};
void BR24T512::write(uint16_t index, uint8_t data){
	uint8_t msb = highByte(index);
	uint8_t lsb = lowByte(index);
	wire->beginTransmission((uint8_t)i2c_addr);
	wire->write(msb);
	wire->write(lsb);
	wire->write(data);
	wire->endTransmission(true);
	delay(5);
};


BR24T512 br24t512;