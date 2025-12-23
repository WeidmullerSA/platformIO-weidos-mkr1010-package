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

#ifndef WEIDOS_MCP23008_H
#define WEIDOS_MCP23008_H

#include <Arduino.h>
#include <Wire.h>
#undef TwoWire_h
#define MCP23008_ADDR 0x21

class MCP23008{
    public:
        MCP23008(uint8_t addr = MCP23008_ADDR, TwoWire* _Wire = &Wire);
        bool begin();
        void setAddress(uint8_t addr);

        // main Arduino API methods
        void pinMode(uint8_t pin, uint8_t mode);
        uint8_t digitalRead(uint8_t pin);
        void digitalWrite(uint8_t pin, uint8_t value);

        void setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity);
        void setupInterruptPin(uint8_t pin, uint8_t mode);
        void disableInterruptPin(uint8_t pin);
    private:
        TwoWire* _Wire = NULL;
        uint8_t i2c_addr;
};


class MCP23008Register{
    public:
        MCP23008Register(uint8_t reg_addr, uint8_t i2c_addr, TwoWire* Wire);
        uint8_t read();
        void write(uint8_t value);
    private:
        uint8_t reg_addr;
        uint8_t i2c_addr;
        TwoWire* _Wire;
};


class RegisterBit{
    public:
        RegisterBit(MCP23008Register* reg, uint8_t bit);
        uint8_t read();
        void write(uint8_t value);
    private:
        MCP23008Register* _register;
        uint8_t _bit;
};

extern MCP23008 mcp23008;

#endif
