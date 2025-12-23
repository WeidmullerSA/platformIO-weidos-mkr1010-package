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

/*
  Read/Write EEPROM example

  Example with the basic user access methods (write/read) 
  and functionality to 'get' and 'put' any data to and from EEPROM.

  
  First, it shows how to read/write a cell (1 byte) from the EEPROM.
  Then two objects, a double and an integer with known values,
  will be saved with E2PROM method put(); this value will be
  recovered with method get() and stored to a new variables intialized to 0.
  To check that the put/get methods were successful, those new
  variables with the read value will be printed.
 */
 
#include <E2PROM.h>

#define BYTE_INDEX      0     //Index for the first cell where a byre (1 byte) will be saved.
#define DOUBLE_INDEX    1     //Index for the first cell where a double (8 bytes) will be saved.
#define INT_INDEX       9     //Index for the first cell where an integer (4 bytes) will be saved.
#define NEXT_INDEX      13    //Index for the next cell index that must be used in case one wants to save more data.


uint8_t byteToSave = 23;      //Variable of type uint8_t whose value will be written to the EEPROM.
uint8_t readByte   = 0;       //Variable where byte read from EEPROM will be stored.
                              //Initialized to 0 to show how it changes when reading from EEPROM.
                              
double doubleToSave = 3.1416; //Variable of type double whose value will be written to the EEPROM.
double readDouble   = 0.0;    //Variable where double read from EEPROM will be stored.
                              //Initialized to 0.0 to show how it changes when reading from EEPROM.

int intToSave = 1995;         //Variable of type int whose value will be written to the EEPROM.
int readInt = 0;              //Variable where integer read from EEPROM will be stored.
                              //Initialized to 0 to show how it changes when reading from EEPROM.



void setup() {
  Serial.begin(115200);
  while(!Serial){};
  delay(5000);
  
  E2PROM.begin();
  Serial.println("Beginning Write/Read operation");
  
  E2PROM.write(BYTE_INDEX, byteToSave);           //write one byte.
  readByte = E2PROM.read(BYTE_INDEX);             //read a byte
  Serial.print("readByte: ");
  Serial.println(readByte);
         
  E2PROM.put(DOUBLE_INDEX, doubleToSave);         //Saving "doubleToSave" to the EEPROM.
  E2PROM.get(DOUBLE_INDEX, readDouble);           //Getting the value stored in the EEPROM to "readDouble".
  Serial.print("readDouble: ");                   //Print value stored in variable "readDouble"
  Serial.println(readDouble);

  E2PROM.put(INT_INDEX, intToSave);               //Saving "intToSave" to the EEPROM.
  E2PROM.get(INT_INDEX, readInt);                 //Getting the value stored in the EEPROM to "readInt".
  Serial.print("readInt: ");                      //Print value stored in variable "readInt"
  Serial.println(readInt);
}

void loop() {
  Serial.println("Write/Read operation has ended!");
  Serial.print("If you have not seen the result printed in the Serial Monitor ");
  Serial.println("run again the example and open the Serial Monitor within 5 seconds after the reset.");
  delay(3000);
}
