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

#ifndef PINS_WEIDOS_H
#define PINS_WEIDOS_H

//####Weidmuller####

//RS485 - UART
#define A_RS485 (14)
#define B_RS485 (13)
#define Tx_0    (14)
#define Rx_0    (13)
#define RTE_DE  (5)
static const uint32_t pin11 = A_RS485;
static const uint32_t pin12 = B_RS485;
static const uint32_t pin14 = RTE_DE;

//RS485 macros to be used in the library.
#define RS485_TX (14)
#define RS485_DE (5)
#define RS485_RE (5)
//UART macro to use Serial1 with this name.
#define UART Serial1

//Analog/Digital inputs
#define ADI_0 (17u)
#define ADI_1 (16u)
#define ADI_2 (20u)
#define ADI_3 (21u)
static const uint32_t pin15 = ADI_0;
static const uint32_t pin16 = ADI_1;
static const uint32_t pin17 = ADI_2;
static const uint32_t pin18 = ADI_3;

//Digital inputs
#define DI_4 (25u)
#define DI_5 (1u)
#define DI_6 (2u)
#define DI_7 (3u)
static const uint32_t pin25 = DI_4;
static const uint32_t pin26 = DI_5;
static const uint32_t pin27 = DI_6;
static const uint32_t pin28 = DI_7;

//Multifunction pins
#define MF_0    (19)
#define MF_1    (0)
static const uint32_t pin41 = MF_0;
static const uint32_t pin42 = MF_1;

//Analog output
#define AO_0 (15u)
static const uint32_t pin45 = AO_0;

//SPI pins
#define MISO_0  (10)
#define MOSI_0  (8)
#define SCK_0   (9)
#define CS      (4)
static const uint32_t pin51 = MISO_0;
static const uint32_t pin52 = MOSI_0;
static const uint32_t pin53 = SCK_0;
static const uint32_t pin54 = CS;

//Digital outputs
#define DO_0 (0x2100)
#define DO_1 (0x2101)
#define DO_2 (0x2102)
#define DO_3 (0x2103)
static const uint32_t pin55 = DO_0;
static const uint32_t pin56 = DO_1;
static const uint32_t pin57 = DO_2;
static const uint32_t pin58 = DO_3;


//I2C pins
#define SDA_0  (11)
#define SCL_0  (12)
static const uint32_t pin61 = SDA_0;
static const uint32_t pin62 =SCL_0;


//Macros for libraries
#define HAVE_MCP23008

#define SDCARD_SS_PIN (0x2106)      //SD slave select/chip select
#define ETHERNET_CS (6u)            //Ethernet slave select/chip select

// LoRa module
#ifdef WEIDOS_LORA
#define HAVE_RN2XX3
#define HAVE_PIC
#define RN2XX3_RESET_PIN (0x2301)
#endif


#ifdef WEIDOS_NBIOT
#define HAVE_PIC
//SARA
#define SARA_RESETN (0x2301)
#define SARA_PWR_ON (0x2300)

#define SerialSARA                   SerialPIC
#endif

//####Weidmuller####
#endif

