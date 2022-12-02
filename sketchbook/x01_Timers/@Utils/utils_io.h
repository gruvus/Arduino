// utils_io.h

#ifndef _UTILS_IO_h
#define _UTILS_IO_h

#include "arduino.h"


struct hwPinInfo_t {
	byte hw_pin;
	volatile uint8_t* reg_in;
	volatile uint8_t* reg_out;
	byte port_pin;
	char pout_bit_name[7]="";
	char pin_bit_name[6]="";
};

bool hwPinToPortInfo(const byte ino_pin, hwPinInfo_t& pinmap);

void showPinInfo(byte hwpin);
void showPinInfo(byte hwpin, bool with_header);
void showPinInfo(byte hwpin, char* function, bool with_header);


#endif