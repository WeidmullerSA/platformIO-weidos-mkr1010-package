#ifndef __LoRa_H__
#define __LoRa_H__

#include <Arduino.h>
#ifdef HAVE_RN2XX3
#include <rn2xx3.h>

enum RadioError{
	RADIO_OK = 0,
	RADIO_INVALID_PARAM = 1,
	RADIO_BUSY = 2,
	RADIO_TIMEOUT = 3
};

class LoRaClass : public rn2xx3 {
	public:
		explicit LoRaClass(HardwareSerial& _serial);

	public:
		/**
		 * Initialize LoRa chip
		*/
		void begin();


		/**
		 * Perform a reset on the LoRa chip.
		*/
		void reset();


		/**
		 * Send data via LoRaWAN protocol. Message can be sent with confirmation (confirmed = true)
		 * or without (confirmation = false).
		 *
		 * @param data String with all data to be sent
		 * @param confirmed True to send message with confirmation, false otherwise.
		 *
		 * @return TX return type with the result of the operation: 0 = TX_FAIL, 1 = TX_SUCCESS, 2 = TX_WITH_RX (downlink message received) 
		*/
		TX_RETURN_TYPE send(const String& data, bool confirmed = false);

		/**
		 * Receiv data via LoRa.
		 * @return String with data received in hexadecimal form.
		*/
		String radioRx();

		/**
		 * Transmit data via LoRa. Only hexadecimal values allowed (0123456789ABCDEF)
		 * @param data String with data to transmit.
		 * @return RadioError with the result of the operation: 0 = RADIO_OK, 1 = RADIO_INVALID_PARAM, 2 = RADIO_BUSY, 3 = RADIO_TIMEOUT
		*/
		RadioError radioTx(const String& data);

	private:
		HardwareSerial& _serial;
};

extern LoRaClass LoRa;
#endif

#endif // __LoRa_H__
