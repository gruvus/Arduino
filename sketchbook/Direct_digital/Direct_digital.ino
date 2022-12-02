
#include "utils.h"
/*
* TEST_CASE 3	// pin_map function ino_pin  -> port, pin#
* TEST_CASE 2   // direct port write | use port pointer and pin mapping macros
* TEST_CASE 1	// early direct port toggle | UNO and DUE
* TEST_CASE 0	// template
*/

#define TEST_CASE 3

// macros for setting test pins
#if TEST_CASE==4

const byte tst_pin = 8;		// PORTB0
const byte sync_pin = 12;	// PORTB4 
const byte led_pin = 13;	// PORTB5


#define SetTimingPin() 		PORTB |= (1 << PORTB0)  // set timing probe (pin 8)
#define ClearTimingPin() 	PORTB &= ~(1 << PORTB0) // clear timing probe (pin 8)
#define ToggleSyncPin() 	PINB |= (1 << PINB4) // toggle sync signal (pin )



void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\nDirect digital i/o ; TestCase "); Serial.print(TEST_CASE); Serial.print("\n");

	pinMode(tst_pin, OUTPUT);
	pinMode(sync_pin, OUTPUT);
	pinMode(led_pin, OUTPUT);

}

void loop() {
	ToggleSyncPin();
	SetTimingPin();

	for (long i = 1; i < 10; i++) {
		byte hp = i % 2;
		//digitalWrite(led_pin, hp);
		PINB |= (1 << PINB5);
	}

	ClearTimingPin();
}

#endif

// test-dev hwPinToPortInfo *********************
#if TEST_CASE==3


void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\n  Direct digital i/o ; TestCase "); Serial.print(TEST_CASE);
	Serial.print("  Get runtime hw pin information for direct access"); NL;

	//allPinsInfo();
	test();
}

void loop() {}



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

		// using my hwPinToPortInfo
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

		// using "digitalPinTo .." functions/macros
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
				//found = (mask >> i) & 0x01;
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

// timing: direct port write | use port pointer and "digitalPinTo .." std mapping macros
#if TEST_CASE ==2	// direct port write | use port pointer and pin mapping macros

const byte tst_pin = 8;		// PORTB0
const byte sync_pin = 12;	// PORTB4 


#define SetTimingPin() 		PORTB |= (1 << PORTB0)  // set timing probe (pin 8)
#define ClearTimingPin() 	PORTB &= ~(1 << PORTB0) // clear timing probe (pin 8)
#define ToggleSyncPin() 	PINB |= (1 << PINB4) // toggle sync signal (pin )


uint8_t port;
uint8_t mask;
volatile uint8_t* portx_p;


void setup() {
	Serial.begin(115200);


	pinMode(tst_pin, OUTPUT);
	pinMode(sync_pin, OUTPUT);

	mask = digitalPinToBitMask(tst_pin);
	port = digitalPinToPort(tst_pin);
	portx_p = portOutputRegister(port);

	Serial.print("\tPin\tPort\tBit\tMask\n");
	Serial.print("\t");
	Serial.print(tst_pin); Serial.print("\t");
	Serial.print(port); Serial.print("\t");
	Serial.print(mask); Serial.print("\t");
	Serial.print(mask, BIN); Serial.print("\t");
	Serial.print("\n");

	ClearTimingPin();

}

void loop() {

	ToggleSyncPin();
	{
		SetTimingPin();		// 1us/(4*2) = 0.125us (2cks)
		ClearTimingPin();
		SetTimingPin();
		ClearTimingPin();
		SetTimingPin();
		ClearTimingPin();
		SetTimingPin();
		ClearTimingPin();
		SetTimingPin();
		ClearTimingPin();
	}

	//ToggleSyncPin();
	{
		*portx_p |= mask; // 2.5us/(4*2) = 0.3125us (5cks)
		*portx_p &= ~mask;
		*portx_p |= mask;
		*portx_p &= ~mask;
		*portx_p |= mask;
		*portx_p &= ~mask;
		*portx_p |= mask;
		*portx_p &= ~mask;
		*portx_p |= mask;
		*portx_p &= ~mask;
	}

	{
		digitalWrite(tst_pin, HIGH); // ~22.7us/(4*2) = ~2.8us
		digitalWrite(tst_pin, LOW);
		digitalWrite(tst_pin, HIGH);
		digitalWrite(tst_pin, LOW);
		digitalWrite(tst_pin, HIGH);
		digitalWrite(tst_pin, LOW);
		digitalWrite(tst_pin, HIGH);
		digitalWrite(tst_pin, LOW);
		digitalWrite(tst_pin, HIGH);
		digitalWrite(tst_pin, LOW);
	}

	ToggleSyncPin();

}

#endif

// early direct port toggle | UNO and DUE
#if TEST_CASE==1
const int L_PIN = LED_BUILTIN;

#ifdef ARDUINO_SAM_DUE
const int TST_PIN = 13;
const float T0 = 4.7 + 0.35; // overheads: loop() ~ 2.35us; while() ~0.35us 
#else
const int TST_PIN = 13;
const float T0 = 4.7 + 0.35; // overheads: loop() ~ 2.35us; while() ~0.35us 
#endif


//#define DIRECT_IO


void loop() {

	digitalWrite(TST_PIN, LOW);    // turn the LED offW

	while (true) {
#ifdef DIRECT_IO
		digitalWrite(TST_PIN, LOW);    // turn the LED offW
		//delayMicroseconds(dly);
		digitalWrite(TST_PIN, HIGH);   // turn the LED on 
		//delayMicroseconds(dly);
#else
#ifdef ARDUINO_SAM_DUE

#else
		PINB |= (1 << PINB5);	// writing 1 to IN port bit toggles bit // ~2MHz on Uno
		PINB |= (1 << PINB5);	// writing 1 to IN port bit toggles bit // ~2MHz on Uno
		PINB |= (1 << PINB5);	// writing 1 to IN port bit toggles bit // ~2MHz on Uno
		PINB |= (1 << PINB5);	// writing 1 to IN port bit toggles bit // ~2MHz on Uno

#endif
#endif

	}
}


void setup() {
	pinMode(TST_PIN, OUTPUT);
	Serial.begin(115200);

	Serial.print("\n\n\nDirect digital out\n");

#ifdef ARDUINO_SAM_DUE
	uint8_t PIN_TO_PORT = digitalPinToPort(TST_PIN);
	uint8_t PIN_TO_BITMASK = digitalPinToBitMask(TST_PIN);
	volatile uint8_t* PIN_TO_INREGISTER = portInputRegister(TST_PIN);

	uint16_t VALUE = *(portInputRegister(TST_PIN));

	Serial.print("  digitalPinToPort\t"); Serial.print(PIN_TO_PORT); Serial.print("\t\n");
	Serial.print("* digitalPinToPort\t"); Serial.print(VALUE, HEX); Serial.print("\t\n");

#else	// UNO
	Serial.print("PINB\t"); Serial.print(PINB); Serial.print("\t\n");
	PINB |= (1 << PINB5);
	Serial.print("PINB\t"); Serial.print(PINB); Serial.print("\t\n");
	PINB |= (1 << PINB5);
	Serial.print("PINB\t"); Serial.print(PINB); Serial.print("\t\n");
	PINB |= (1 << PINB5);
	Serial.print("PINB\t"); Serial.print(PINB); Serial.print("\t\n");
	PINB |= (1 << PINB5);
#endif
}

#endif

// template
#if TEST_CASE==0

void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\nDirect digital i/o ; TestCase "); Serial.print(TEST_CASE); Serial.print("\n");


}

void loop() {

}

#endif




