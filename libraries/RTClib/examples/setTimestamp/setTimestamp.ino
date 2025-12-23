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
 * This program has to be uploaded to the Weidos only once to set the local time in our RTC. 
 * In this case it takes the local time of our PC as the starting point to start counting, 
 * but the rtc.adjust() function accepts another time to start counting.
 * 
 * It is important to emphasize that this program only has to be passed once to set the current time, 
 * from then on the RTC can always be consulted. 
 * 
 */

#include <Arduino.h>
#include <RTClib.h>
 

RTC_DS3231 rtc;   // Declare RTC DS3231
 
void setup () {
 Serial.begin(9600);
 
 // Check RTC is connected
 if (! rtc.begin()) {
 Serial.println("No RTC Module");
 while (1);
 }
 
//  THIS LINE HAS TO BE EXECUTED ONLY ONE TIME. THE CURRENT TIME IS TAKEN FROM THE PC

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.begin();
}
 
void loop () {
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
  Serial.println("RTC correctly setted. Please upload another program that makes use of it.");
}
