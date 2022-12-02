

//#include "utils.h"

#include "utils_bits.h"


void printBits(uint8_t v) {
	const byte N = 8;
	for (int i = N - 1; i >= 0; i--) {
		if (i == 3)		Serial.print(" ");
		Serial.print(bitRead(v, i));
	}
}


void printBits(uint16_t v) {
	const byte N = 16;
	for (int i = N - 1; i >= 0; i--) {
		if (i == 3)		Serial.print(" ");
		if (i == 7)		Serial.print(" ");
		if (i == 11)		Serial.print(" ");

		Serial.print(bitRead(v, i));
	}
}

void printBitsAlt(uint8_t v) {
	const byte N = 8;

	for (int i = N - 1; i >= 0; i--) {
		if (i == 3)		Serial.print(" "); //extra space

		Serial.print(" ");
		Serial.print(bitRead(v, i));
	}
}
