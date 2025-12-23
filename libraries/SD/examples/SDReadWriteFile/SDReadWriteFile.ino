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
  SD Write and Read File example

   Write two text lines into a ".txt" file and then reads this file
   and prints all data in Serial Monitor. 
*/


#include <SD.h>
File myFile;
String fileName = "example.txt";    //Maximum name's length is 13 characters (including extension ".txt").


void setup() {
  Serial.begin(115200);
  delay(5000);
  while (!Serial){}

  if (!SD.begin()) {
      Serial.println("initialization failed. Things to check:");
      Serial.println("1. is a card inserted?");
      Serial.println("Note: press reset or reopen this Serial Monitor after fixing your issue!");
      while (true);
   }

    
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(fileName, FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to " + fileName +"...");
    myFile.println("This is a text for an example file. \nThis is a new line for test.");
    myFile.close(); 
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + fileName);
  }

  // re-open the file for reading:
  myFile = SD.open(fileName);
  Serial.println("Reading the file...");
  if (myFile) {
    Serial.println(fileName);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();  // close the file:
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + fileName);
  }
}

void loop() {
  Serial.println("Write/Read operation has ended!");
  Serial.print("If you have not seen the result printed in the Serial Monitor ");
  Serial.println("run again the example and open the Serial Monitor within 5 seconds after the reset.");
  delay(3000);
}
