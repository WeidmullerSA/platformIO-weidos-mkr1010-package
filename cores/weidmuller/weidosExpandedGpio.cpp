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

#include "Arduino.h"
#include "weidosExpandedGpio.h"
#include "weidos_mcp23008.h"

#define expandedPinToDeviceIndex(p) (p & 0xff)
#define expandedPinToDeviceAddress(x) (x>>8)
#define isExpandedPin(p) (p > 0xff)


void initExpandedGpio(){
    #ifdef HAVE_MCP23008
    mcp23008.begin();
    #endif
    return;
}


extern "C"{
    void _digitalWrite( pin_size_t ulPin, PinStatus ulVal);
    void _pinMode( pin_size_t ulPin, PinMode ulMode);
}


void pinMode( pin_size_t ulPin, PinMode ulMode)
{
  // Handle the case the pin isn't usable as PIO
    if(!isExpandedPin(ulPin)){
        _pinMode(ulPin, ulMode);
        return;
    }

    #ifdef HAVE_MCP23008
    mcp23008.setAddress(expandedPinToDeviceAddress(ulPin));
    mcp23008.pinMode(expandedPinToDeviceIndex(ulPin), ulMode);
    #endif
    return;
}
    

void digitalWrite( pin_size_t ulPin, PinStatus ulVal)
{
    if(!isExpandedPin(ulPin)){
        _digitalWrite(ulPin, ulVal);
        return;
    }
    #ifdef HAVE_MCP23008
    mcp23008.setAddress(expandedPinToDeviceAddress(ulPin));
    mcp23008.digitalWrite(expandedPinToDeviceIndex(ulPin), ulVal);
    #endif
    return;
}
