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

#include <weidos_mcp23008.h>


#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A



MCP23008::MCP23008(uint8_t addr, TwoWire* _Wire){
    i2c_addr = addr;
    this->_Wire = _Wire;
};
bool MCP23008::begin(){
    _Wire->begin();
    return true;
};
void MCP23008::setAddress(uint8_t addr){
    i2c_addr = addr;
    return;
};
void MCP23008::pinMode(uint8_t pin, uint8_t mode){
    MCP23008Register IODIR(MCP23008_IODIR, i2c_addr, _Wire);
    RegisterBit dirBit(&IODIR, pin);

    MCP23008Register GPPU(MCP23008_GPPU, i2c_addr, _Wire);
    RegisterBit pullupBit(&GPPU, pin);

    dirBit.write((mode == OUTPUT) ? 0 : 1);
    pullupBit.write((mode == INPUT_PULLUP) ? 1 : 0);  
};
uint8_t MCP23008::digitalRead(uint8_t pin){
    MCP23008Register GPIO(MCP23008_GPIO, i2c_addr, _Wire);
    RegisterBit pinBit(&GPIO, pin);
    return (pinBit.read() == 0) ? LOW : HIGH;
};
void MCP23008::digitalWrite(uint8_t pin, uint8_t value){
    MCP23008Register GPIO(MCP23008_GPIO, i2c_addr, _Wire);
    RegisterBit pinBit(&GPIO, pin);
    pinBit.write((value == LOW) ? 0 : 1);
    return;
};
void MCP23008::setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity) {
  MCP23008Register IOCON(MCP23008_IOCON, i2c_addr, _Wire);
  RegisterBit mirror_bit(&IOCON, 6);
  RegisterBit openDrain_bit(&IOCON, 2);
  RegisterBit polarity_bit(&IOCON, 1);

  mirror_bit.write(mirroring ? 1 : 0);
  openDrain_bit.write(openDrain ? 1 : 0);
  polarity_bit.write((polarity == HIGH) ? 1 : 0);
}
void MCP23008::setupInterruptPin(uint8_t pin, uint8_t mode) {
  MCP23008Register GPINTEN(MCP23008_GPINTEN, i2c_addr, _Wire);
  MCP23008Register INTCON(MCP23008_INTCON, i2c_addr, _Wire);
  MCP23008Register DEFVAL(MCP23008_DEFVAL, i2c_addr, _Wire);
  RegisterBit enable_bit(&GPINTEN, pin);
  RegisterBit config_bit(&INTCON, pin);
  RegisterBit defval_bit(&DEFVAL, pin);

  enable_bit.write(1);                        // enable it
  config_bit.write((mode == CHANGE) ? 0 : 1); // set mode
  defval_bit.write((mode == LOW) ? 1 : 0);    // set defval
}
void MCP23008::disableInterruptPin(uint8_t pin) {
  MCP23008Register GPINTEN(MCP23008_GPINTEN, i2c_addr, _Wire);
  RegisterBit enable_bit(&GPINTEN, pin);

  enable_bit.write(0);
}


MCP23008Register::MCP23008Register(uint8_t reg, uint8_t i2c_addr, TwoWire* Wire){
    reg_addr = reg;
    this->i2c_addr = i2c_addr;
    _Wire = Wire;
    return;
}
uint8_t MCP23008Register::read(){
    _Wire->beginTransmission(i2c_addr);
    _Wire->write(reg_addr);
    _Wire->endTransmission(false);
    _Wire->requestFrom(i2c_addr, 1);
    return  _Wire->read();
};
void MCP23008Register::write(uint8_t value){
    _Wire->beginTransmission(i2c_addr);
    _Wire->write(reg_addr);
    _Wire->write(value);
    _Wire->endTransmission(true);
};



RegisterBit::RegisterBit(MCP23008Register* reg, uint8_t bit){
    _register = reg;
    _bit = bit;
}
uint8_t RegisterBit::read(){
    uint8_t reg = _register->read();
    reg = reg & (1<<_bit);  //Masking all bits except the one corresponding to the pin
    return reg>>_bit;
};
void RegisterBit::write(uint8_t value){
    uint8_t reg = _register->read();
    reg = reg & ~(1<<_bit);
    reg = reg | (value<<_bit);
    _register->write(reg);
    //value = value & (1<<_bit);  //Masking all bits except the one corresponding to the pin
    //return value>>_bit;
    return;
};


MCP23008 mcp23008;