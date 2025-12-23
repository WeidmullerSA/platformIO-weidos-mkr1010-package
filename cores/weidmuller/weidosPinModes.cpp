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
#include "weidosPinModes.h"


void weidos_initDefaultIOPins(){

    //Digital inputs
    pinMode(pin25, INPUT);	//DI_4
	pinMode(pin26, INPUT);	//DI_5
	pinMode(pin27, INPUT);	//DI_6
	pinMode(pin28, INPUT);	//DI_7
	
	//Digital outputs
	digitalWrite(pin55, LOW);
    digitalWrite(pin56, LOW);
    digitalWrite(pin57, LOW);
    digitalWrite(pin58, LOW);
	pinMode(pin55, OUTPUT); //DO_0
	pinMode(pin56, OUTPUT); //DO_1
	pinMode(pin57, OUTPUT); //DO_2
	pinMode(pin58, OUTPUT); //DO_3

	//Analog  inputs (Can also be used as digital inputs)
	pinMode(pin15, INPUT);	//ADI_0
	pinMode(pin16, INPUT);	//ADI_1
	pinMode(pin17, INPUT);	//ADI_2
	pinMode(pin18, INPUT);	//ADI_3

	//Analog output
	analogWrite(pin45, 0);	//AO_0

	pinMode(SDCARD_SS_PIN, OUTPUT);
	digitalWrite(SDCARD_SS_PIN, HIGH);

	pinMode(ETHERNET_CS, OUTPUT);
	digitalWrite(ETHERNET_CS, HIGH);

	pinMode(CS, OUTPUT);
	digitalWrite(CS, HIGH);

	//SARA R412 NBIOT chip
	#ifdef WEIDOS_NBIOT
	pinMode(SARA_PWR_ON, OUTPUT);
  	digitalWrite(SARA_PWR_ON, LOW);
  	pinMode(SARA_RESETN, OUTPUT);
  	digitalWrite(SARA_RESETN, LOW);
	#endif
}
