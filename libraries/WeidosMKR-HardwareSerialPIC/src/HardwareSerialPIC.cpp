#include "HardwareSerialPIC.h"

#ifdef HAVE_PIC

#include <Wire.h>

#define FIFO_SIZE					400

#define FIFO_RX_REGISTER			0x00
#define FIFO_TX_REGISTER			0x00
#define FIFO_TX_AVAILABLE_REGISTER	0x01
#define FIFO_RX_PENDING_REGISTER	0x02
#define RESET_REGISTER				0x7b

////////////////////////////////////////////////////////////////////////////////////////////////////
HardwareSerialPIC::HardwareSerialPIC(uint8_t i2cAddr) : i2cAddr(i2cAddr) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::begin(unsigned long baud) {
	begin(baud, SERIAL_8N1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::begin(unsigned long baud, uint16_t config) {
	Wire.begin();
	reset();
	// Set baudrate
	setBaudrate(baud);
	
	_pendingBufferReadBytes = 0;
  	_counterReadBytes = 0;
  	_updatedReadBytes = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::end() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::reset(){
	Wire.beginTransmission(i2cAddr);
	Wire.write(RESET_REGISTER);
	Wire.endTransmission();
	delay(100);
	
 	_pendingBufferReadBytes = 0;
  	_counterReadBytes = 0;
  	_updatedReadBytes = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::setBaudrate(unsigned long baud) {
	Wire.beginTransmission(i2cAddr);
	Wire.write(baud);
	Wire.endTransmission();	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::write(uint8_t value) {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_TX_REGISTER);
	Wire.write(value);
	Wire.endTransmission();
	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::write(const uint8_t *buffer, size_t size) {
	uint8_t i = 0;
  	Wire.beginTransmission(i2cAddr);
  	Wire.write(FIFO_TX_REGISTER);
  	size_t pending = size;
 	while (pending--) {
    	Wire.write(*buffer++);
    	delay(1);
    	if(i++ == 100) { //254      	
			Wire.endTransmission();
			// Clean reading buffer
			if(available()){
	    		_bufferReadBytes[_counterReadBytes++] = readAndSave();
	  		}
			// End reading
			Wire.beginTransmission(i2cAddr);
			Wire.write(FIFO_TX_REGISTER);
			i=0;
      	}
  	}
  	Wire.endTransmission();	
  	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::available() {
	uint16_t ret;
	
  	if(_pendingBufferReadBytes != 0) {			
    	return _pendingBufferReadBytes;
    }

  	if(_updatedReadBytes < _counterReadBytes) {		
    	return _counterReadBytes - _updatedReadBytes;
    }
		
  	_updatedReadBytes = 0;
  	_counterReadBytes = 0;

  	do {
    	do {
	  		do {
	      		Wire.beginTransmission(i2cAddr);
	      		Wire.write(FIFO_RX_PENDING_REGISTER);

	    	} while (Wire.endTransmission() != 0);

	  		Wire.requestFrom(i2cAddr, 2);

		} while (Wire.available() != 2);

      	ret = Wire.read();
      	ret |= Wire.read() << 8;
      	_pendingBufferReadBytes = ret;

    } while (ret > 800);

  	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::availableForWrite() {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_TX_AVAILABLE_REGISTER);
	Wire.endTransmission();

	Wire.requestFrom(i2cAddr, 2);
	if (Wire.available() != 2) {
		return 0;
	}

	uint16_t ret = Wire.read();
	ret |= Wire.read() << 8;

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::read() {
	// Check saved bytes  
  	if(_updatedReadBytes != _counterReadBytes) {
    	return _bufferReadBytes[_updatedReadBytes++];
    }

  	_updatedReadBytes = 0;
  	_counterReadBytes = 0;

  	uint16_t numberReadBytes = available();

 	if(!numberReadBytes) {
    	return -1;
    }

  	if(numberReadBytes > 250) 
    	numberReadBytes = 250;
	
	
  	Wire.beginTransmission(i2cAddr);
  	Wire.write(FIFO_RX_REGISTER);
  	Wire.endTransmission();
  	Wire.requestFrom(i2cAddr, numberReadBytes);
  	if (Wire.available() != numberReadBytes) {
    	return -1;
  	}
	
  	while(numberReadBytes-- != 0) {
    	if(_pendingBufferReadBytes > 0)
			_pendingBufferReadBytes--;
      	_bufferReadBytes[_counterReadBytes++] = Wire.read();
    }

  	return _bufferReadBytes[_updatedReadBytes++];
}

//////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::readAndSave() {
	// Check saved bytes
  	uint16_t numberReadBytes = available();	

  	do {
    	do {
			do {
	    		Wire.beginTransmission(i2cAddr);
	      		Wire.write(FIFO_RX_PENDING_REGISTER);
	    	} while (Wire.endTransmission() != 0);

			Wire.requestFrom(i2cAddr, 2);
		} while(Wire.available() != 2); 

      	numberReadBytes = Wire.read();
      	numberReadBytes |= Wire.read() << 8;
    } while (numberReadBytes > 800);

  	if(!numberReadBytes) {
    	return -1;
    }

  	if(numberReadBytes > 250)
    	numberReadBytes = 250;

  	Wire.beginTransmission(i2cAddr);
  	Wire.write(FIFO_RX_REGISTER);
  	Wire.endTransmission();
  	Wire.requestFrom(i2cAddr, numberReadBytes);
  	if (Wire.available() != numberReadBytes) {	
    	return -1;
  	}

  	while(numberReadBytes-- != 0) {
    	if(_pendingBufferReadBytes > 0)
			_pendingBufferReadBytes--;
      	_bufferReadBytes[_counterReadBytes++] = Wire.read();
    }
	
  	return _bufferReadBytes[_updatedReadBytes];
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::read(uint8_t* buff, size_t size) {
	if(!available()) return -1;

	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_RX_REGISTER);
	Wire.endTransmission();	

	Wire.requestFrom(i2cAddr, size);
	if (Wire.available() != size) {
		return -1;
	}

	size_t pending = size;
	while (pending--) {
		*buff++ = Wire.read();
	}
	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::peek(void) {
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::flush() {
	while (availableForWrite() < FIFO_SIZE) {
		delay(1);
	}
}


HardwareSerialPIC SerialPIC(PIC_I2C_ADDRESS);

#endif		// HAVE_PIC
