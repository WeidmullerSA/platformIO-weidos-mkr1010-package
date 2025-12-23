#ifndef __HARDWARE_SERIAL_PIC_H__
#define __HARDWARE_SERIAL_PIC_H__

#include <Arduino.h>
#ifdef HAVE_PIC


#define PIC_I2C_ADDRESS 120
#define RX_BUFFER 1500

class HardwareSerialPIC : public HardwareSerial {
	public:
		enum BaudRate {
			BaudRate_300	= 10,
			BaudRate_1200	= 11,
			BaudRate_2400	= 12,
			BaudRate_4800	= 13,
			BaudRate_9600	= 14,
			BaudRate_19200	= 15,
			BaudRate_38400	= 16,
			BaudRate_57600	= 17,
			BaudRate_74880	= 18,
			BaudRate_115200	= 19,
			BaudRate_230400	= 20,
			BaudRate_250000	= 21,
		};

	public:
		HardwareSerialPIC(uint8_t i2cAddr = PIC_I2C_ADDRESS);

	public:
		virtual void begin(unsigned long baud);
		virtual void begin(unsigned long baud, uint16_t config);
		virtual void end();
		virtual void reset();

		void setBaudrate(unsigned long baud);

		virtual size_t write(uint8_t value);
		virtual size_t write(const uint8_t* buff, size_t size);
		using HardwareSerial::write;
		virtual int available();
		virtual int availableForWrite();
		virtual int read();
		virtual size_t read(uint8_t* buff, size_t size);
		virtual int peek();
		virtual void flush();

		virtual operator bool() { return true; }

	private:
		uint8_t i2cAddr;
		uint16_t _pendingBufferReadBytes;
		uint8_t _bufferReadBytes[RX_BUFFER];
		uint16_t _counterReadBytes;
		uint16_t _updatedReadBytes;
		int readAndSave(void);
};

extern HardwareSerialPIC SerialPIC;
#endif		// HAVE_PIC

#endif		// __HARDWARE_SERIAL_PIC_H__
