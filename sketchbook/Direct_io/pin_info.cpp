// 
// 
// 

#include "pin_info.h"


#ifdef ARDUINO_AVR_UNO
void allPinsInfo() {

	auto header_and_margin = [](byte hwpin) {
		if (hwpin == 0)
		{
			Serial.print("\n ");
			Serial.print("hw_pin"); TAB;
			Serial.print("r_in"); TAB;
			Serial.print("r_out"); TAB;
			Serial.print("bit#"); TAB;
			Serial.print("out_id"); TAB;
			Serial.print("in_id"); TAB;

			Serial.print("hwpin"); TAB;
			Serial.print("port#"); TAB;
			Serial.print("i_reg"); TAB;
			Serial.print("o_reg"); TAB;
			Serial.print("mask"); TAB;
			Serial.print("mask bin"); TAB;
			Serial.print("bit#"); TAB;

			NL;
			for (byte i = 0; i < 14; i++) {
				Serial.print("======="); TAB;
			}NL;
		}
		Serial.print("  ");
	};

	for (byte hwpin = 0; hwpin <= 19; hwpin++) {

		header_and_margin(hwpin);

		//using my hwPinToPortInfo
		{
			hwPinInfo_t pin_info;

			if (hwPinToPortInfo(hwpin, pin_info)) {
				Serial.print(pin_info.hw_pin); TAB;
				Serial.print((uint8_t)pin_info.reg_in, HEX); TAB;
				Serial.print((uint8_t)pin_info.reg_out, HEX); TAB;
				Serial.print(pin_info.port_pin); TAB;
				Serial.print(pin_info.pout_bit_name); TAB;
				Serial.print(pin_info.pin_bit_name); TAB;

			}
			else
				Serial.print("Invalid pin value");
		}

		//using "digitalPinTo .." functions/macros
		{
			uint8_t mask = digitalPinToBitMask(hwpin);
			uint8_t port = digitalPinToPort(hwpin);
			volatile uint8_t* outreg_p = portOutputRegister(port);
			volatile uint8_t* inreg_p = portInputRegister(port);

			Serial.print(hwpin); TAB;
			Serial.print(port, HEX); TAB;
			Serial.print((byte)outreg_p, HEX); TAB;
			Serial.print((byte)inreg_p, HEX); TAB;
			Serial.print(mask); TAB;
			printBits(mask); TAB;

			bool found = false;
			byte i;
			for (i = 0; i < 8; i++) {
				found = bitRead(mask, i);
				found = (mask >> i) & 0x01;
				if (found) break;
			}
			if (found)
				Serial.print(i);
			else
				Serial.print("!");
		}

		NL;
	}
}
#endif

#ifdef ARDUINO_AVR_MEGA2560
void allPinsInfo() {

	auto header_and_margin = [](byte hwpin) {
		if (hwpin == 0)
		{
			Serial.print("\n ");
			Serial.print("hw_pin"); TAB;
			Serial.print("r_in"); TAB;
			Serial.print("r_out"); TAB;
			Serial.print("bit#"); TAB;
			Serial.print("out_id"); TAB;
			Serial.print("in_id"); TAB;

			Serial.print("hwpin"); TAB;
			Serial.print("port#"); TAB;
			Serial.print("i_reg"); TAB;
			Serial.print("o_reg"); TAB;
			Serial.print("mask"); TAB;
			Serial.print("mask bin"); TAB;
			Serial.print("bit#"); TAB;

			NL;
			for (byte i = 0; i < 14; i++) {
				Serial.print("======="); TAB;
			}NL;
		}
		Serial.print("  ");
	};

	for (byte hwpin = 0; hwpin <= 13; hwpin++) {

		header_and_margin(hwpin);

		//using my hwPinToPortInfo
		{
			hwPinInfo_t pin_info;

			if (hwPinToPortInfo(hwpin, pin_info)) {
				Serial.print(pin_info.hw_pin); TAB;
				Serial.print((uint8_t)pin_info.reg_in, HEX); TAB;
				Serial.print((uint8_t)pin_info.reg_out, HEX); TAB;
				Serial.print(pin_info.port_pin); TAB;
				Serial.print(pin_info.pout_bit_name); TAB;
				Serial.print(pin_info.pin_bit_name); TAB;

			}
			else
				Serial.print("Invalid pin value");
		}

		//using "digitalPinTo .." functions/macros
		{
			uint8_t mask = digitalPinToBitMask(hwpin);
			uint8_t port = digitalPinToPort(hwpin);
			volatile uint8_t* outreg_p = portOutputRegister(port);
			volatile uint8_t* inreg_p = portInputRegister(port);

			Serial.print(hwpin); TAB;
			Serial.print(port, HEX); TAB;
			Serial.print((byte)outreg_p, HEX); TAB;
			Serial.print((byte)inreg_p, HEX); TAB;
			Serial.print(mask); TAB;
			printBits(mask); TAB;

			bool found = false;
			byte i;
			for (i = 0; i < 8; i++) {
				found = bitRead(mask, i);
				found = (mask >> i) & 0x01;
				if (found) break;
			}
			if (found)
				Serial.print(i);
			else
				Serial.print("!");
		}

		NL;
	}
}
#endif