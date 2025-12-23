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

/**
  Get Timestamp example

  Obtain current time from the RTC every second and prints it to
  the Serial Monitor with format: DD/MM/YYYY/ HH:MM:SS
*/
 
#include <Arduino.h>
#include <RTClib.h>
 

RTC_DS3231 rtc;   // Declare RTC DS3231
 
void setup () {
 Serial.begin(9600);
 while(!Serial){}
 
 // Check RTC is connected
 if (! rtc.begin()) {
   Serial.println("No RTC Module");
   while (1){};
 }
}
 
void loop () {

 rtc.begin();
 DateTime now = rtc.now();
 
 Serial.print(now.day());
 Serial.print('/');
 Serial.print(now.month());
 Serial.print('/');
 Serial.print(now.year());
 Serial.print(" ");
 Serial.print(now.hour());
 Serial.print(':');
 Serial.print(now.minute());
 Serial.print(':');
 Serial.print(now.second());
 Serial.println();
 delay(1000);
}
