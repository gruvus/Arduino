
#include "utils.h"
#include "pin_info.h"

/*
* TEST_CASE 3	// pin_map function ino_pin  -> port, pin#
* TEST_CASE 2   // direct port write | use port pointer and pin mapping macros
* TEST_CASE 1	// early direct port toggle | UNO and DUE
* TEST_CASE 0	// template
*/


#define TEST_CASE 2


// test-dev hwPinToPortInfo *********************
#if TEST_CASE == 3

void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\n  Direct digital i/o ; TestCase ");// Serial.print(TEST_CASE); 
	Serial.print("  Get runtime hw pin information for direct access\n"); NL;

	allPinsInfo();
	

}

void loop() 
{
}
#endif

// timing comparison: direct port write | use port pointer and "digitalPinTo .." std mapping macros
#if TEST_CASE == 2	// direct port write | use port pointer and pin mapping macros

// works on both UNO and MEGA

#define ACTIVITY_PIN 13
#define TIMING_PIN 12
#define SYNC_PIN 8
//#define PROBE_PIN 7
//#define AUX_PIN 6

#include "utils_test_pins.h"

uint8_t port;
uint8_t mask;
volatile uint8_t* portx_p;

void setup() {
	Serial.begin(115200);

	SetupTestPins;

	mask = digitalPinToBitMask(activity_pin);
	port = digitalPinToPort(activity_pin);
	portx_p = portOutputRegister(port);

	Serial.print("\tPin\tPort\tBit\tMask\n");
	Serial.print("\t");
	Serial.print(activity_pin); Serial.print("\t");
	Serial.print(port); Serial.print("\t");
	Serial.print(mask); Serial.print("\t");
	Serial.print(mask, BIN); Serial.print("\t");
	Serial.print("\n");

	ClearTimingPin;

	ToggleSyncPin;


}

void loop() {

	noInterrupts();
	//ToggleSyncPin;

	{
		static bool pass = false;

		uint8_t port;
		uint8_t mask;
		volatile uint8_t* portx_p;

		mask = digitalPinToBitMask(sync_pin);
		port = digitalPinToPort(sync_pin);
		portx_p = portOutputRegister(port);

		if (pass) 
			*portx_p &= ~mask; 
		else 
			*portx_p |= mask;
	
		pass = !pass;
	}



	SetTimingPin;
	{
		SetActivityPin;		// 1us/(4*2) = 0.125us (2cks)
		ClearActivityPin;
		SetActivityPin;
		ClearActivityPin;
		SetActivityPin;
		ClearActivityPin;
		SetActivityPin;
		ClearActivityPin;
		SetActivityPin;
		ClearActivityPin;
	}
	ClearTimingPin;
	SetTimingPin;
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
	ClearTimingPin;

	SetTimingPin;
	{
		digitalWrite(activity_pin, HIGH); // ~22.7us/(4*2) = ~2.8us // 5.3 on Mega ? different or had error on UNO?
		digitalWrite(activity_pin, LOW);
		digitalWrite(activity_pin, HIGH);
		digitalWrite(activity_pin, LOW);
		digitalWrite(activity_pin, HIGH);
		digitalWrite(activity_pin, LOW);
		digitalWrite(activity_pin, HIGH);
		digitalWrite(activity_pin, LOW);
		digitalWrite(activity_pin, HIGH);
		digitalWrite(activity_pin, LOW);
	}
	ClearTimingPin;

}

#endif

// early direct port toggle | UNO and DUE
#if TEST_CASE == 1
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
#if TEST_CASE == 0

void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\nDirect digital i/o ; TestCase "); Serial.print(TEST_CASE); Serial.print("\n");
	test();
}

void loop() {

}

#endif





