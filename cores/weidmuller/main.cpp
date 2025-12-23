/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

 /*
* This file incorporates work covered by the following copyright and
* permission notice:
*/

/*
Copyright (C) 2022 Weidmüller SA. All rights reserved.
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



#define ARDUINO_MAIN
#include "Arduino.h"

#include "weidosPinModes.h"
#include "weidosExpandedGpio.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

extern USBDeviceClass USBDevice;

// Initialize C library
extern "C" void __libc_init_array(void);

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
  init();

  __libc_init_array();

  initVariant();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  initExpandedGpio();
  weidos_initDefaultIOPins();
  analogWriteResolution(10);
  analogReadResolution(12);

  setup();

  for (;;)
  {
    loop();
    if (arduino::serialEventRun) arduino::serialEventRun();
  }

  return 0;
}
