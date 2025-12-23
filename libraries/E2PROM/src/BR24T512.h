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

#ifndef BR24T512_H
#define BR24T512_H

#include <Arduino.h>
#include <Wire.h>

#define BR24T512_ADDR 0x55

class BR24T512 {
public:
	BR24T512();
    void begin(uint8_t i2c_addr = BR24T512_ADDR, TwoWire* wire = &Wire);
	uint8_t read(uint16_t index);
	void write(uint16_t index, uint8_t data);

private:
	uint8_t i2c_addr = BR24T512_ADDR;
	TwoWire* wire = &Wire;
};

extern BR24T512 br24t512;

#endif /* BR24T512_H */