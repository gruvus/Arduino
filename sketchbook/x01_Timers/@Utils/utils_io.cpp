
#include "utils.h"
#include "utils_io.h"


bool hwPinToPortInfo(const byte ino_pin, hwPinInfo_t& pinmap)
{
	auto PORTbitName = [](const byte hw_pin, byte inout, char* pbn)
	{

		if (inout == OUTPUT) {
			strcpy(pbn, "PORT");
		}
		else {
			strcpy(pbn, "PIN");
		}
		switch (hw_pin) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:		strcat(pbn, "D"); break;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:	strcat(pbn, "B"); break;
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:	strcat(pbn, "C"); break;

		default: strcat(pbn, "!");

		}

		switch (hw_pin) {
		case 0:		return strcat(pbn, "0"); break;
		case 1:		return strcat(pbn, "1"); break;
		case 2:		return strcat(pbn, "2"); break;
		case 3:		return strcat(pbn, "3"); break;
		case 4:		return strcat(pbn, "4"); break;
		case 5:		return strcat(pbn, "5"); break;
		case 6:		return strcat(pbn, "6"); break;
		case 7:		return strcat(pbn, "7"); break;
		case 8:		return strcat(pbn, "0"); break;
		case 9:		return strcat(pbn, "1"); break;
		case 10:	return strcat(pbn, "2"); break;
		case 11:	return strcat(pbn, "3"); break;
		case 12:	return strcat(pbn, "4"); break;
		case 13:	return strcat(pbn, "5"); break;
		case 14:	return strcat(pbn, "0"); break;
		case 15:	return strcat(pbn, "1"); break;
		case 16:	return strcat(pbn, "2"); break;
		case 17:	return strcat(pbn, "3"); break;
		case 18:	return strcat(pbn, "4"); break;
		case 19:	return strcat(pbn, "5"); break;

		default: return strcat(pbn, "!");

		}

	};

	pinmap.hw_pin = ino_pin;
	PORTbitName(ino_pin, INPUT, pinmap.pin_bit_name);
	PORTbitName(ino_pin, OUTPUT, pinmap.pout_bit_name);

	if (ino_pin >= 0 && ino_pin <= 7) {
		pinmap.reg_in = &PIND;
		pinmap.reg_out = &PORTD;
		pinmap.port_pin = ino_pin;				//  0 .. 7 -> PD0 .. PD7
	}
	else if (ino_pin >= 8 && ino_pin <= 13) {
		pinmap.reg_in = &PINB;
		pinmap.reg_out = &PORTB;
		pinmap.port_pin = ino_pin - 8;			// 8 ..13 -> PB0 .. PB5
	}
	else if (ino_pin >= 14 && ino_pin <= 19) {	// also A0 to A5
		pinmap.reg_in = &PINC;
		pinmap.reg_out = &PORTC;
		pinmap.port_pin = ino_pin - 14;			// 14 .. 19 -> PC0 .. PC5
	}
	else {
		return false; // invalid  ino pin number
	}

	return true;
}



void showPinInfo(byte hwpin, char* function, bool with_header) {
	auto header_and_margin = [&]() {
		if (with_header) {
			Serial.print("\n  ");
			Serial.print("Function"); TAB;
			Serial.print("hw_pin"); TAB;
			Serial.print("r_in"); TAB;
			Serial.print("r_out"); TAB;
			Serial.print("bit#"); TAB;
			Serial.print("out_id"); TAB;
			Serial.print("in_id"); TAB;
			NL;
			for (byte i = 0; i < 7; i++) {
				if (i==0) Serial.print(" =======");
				Serial.print("======="); TAB;
			}NL;
		}
		Serial.print("  ");
	};

	header_and_margin();

	//using my hwPinToPortInfo

	hwPinInfo_t pin_info;

	if (hwPinToPortInfo(hwpin, pin_info)) {
		Serial.print(function); TAB;
		Serial.print(pin_info.hw_pin); TAB;
		Serial.print((uint8_t)pin_info.reg_in, HEX); TAB;
		Serial.print((uint8_t)pin_info.reg_out, HEX); TAB;
		Serial.print(pin_info.port_pin); TAB;
		Serial.print(pin_info.pout_bit_name); TAB;
		Serial.print(pin_info.pin_bit_name); TAB; TAB;

	}
	else {
		Serial.print(hwpin); TAB;
		Serial.print("Invalid pin value");
	}
	NL;
}


void showPinInfo(byte hwpin, bool with_header) {
	showPinInfo(hwpin, "         ", with_header);
}


void showPinInfo(byte hwpin) {
	showPinInfo(hwpin, "         ", false);
}

