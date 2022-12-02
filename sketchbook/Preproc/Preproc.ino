#define DBG
#define ACTIVITY_PIN 13
#define TIMING_PIN 12
#define SYNC_PIN 8
#define PROBE_PIN 7
#define AUX_PIN 6

#include "utils_test_pins.h"

//#include "utils.h"


#define TEST_CASE 1

 // use macros for test pins; show test pin info
#if TEST_CASE==1

#include "utils.h"


void setup() {
	Serial.begin(115200);
	StartupMessage();

	SetupTestPins;

	showTestPinsInfo();

}

void StartupMessage() {
	Serial.print("\n\n\nPreprocessor directives; TestCase "); Serial.print(TEST_CASE); Serial.print("\n\n");
	//dpr("  Debug printing enabled"); dnl;
	Serial.print("\n ========================================\n\n");
}


void loop() {
	ToggleSyncPin;
	SetTimingPin;

	for (long i = 1; i < 10; i++) {
		byte hp = i % 2;
		//digitalWrite(activity_pin, hp);
		ToggleActivityPin;
	}

	ClearTimingPin;
}


//#define lst(a) Serial.print(a)
//#define TAB Serial.print("\t");
//#define NL Serial.print("\n");
//#define tab TAB
//#define NewLine NL


void showTestPinsInfo() {

	// create pin array
	byte test_pins[5] = { ACTIVITY_PIN, TIMING_PIN, SYNC_PIN, PROBE_PIN, AUX_PIN };
	char* test_names[5] = { ActivityPinName, TimingPinName, SyncPinName, ProbePinName, AuxPinName };

	// max length
	byte l = 0, n = 0;
	for (byte i = 0; i < 5; i++) {
		if (test_pins[i] < MAX_TEST_PIN) { // only include defined pins
			l = max(l, strlen(test_names[i]));
			n++;
		}
	}
	if (n == 0)
		lst("\nNo test pins defined\n");
	else {
		// at least one defined 

		//showTestPinsInfo();
		bool header = true; const byte L = 10;
		for (byte i = 0; i < 5; i++) {
			if (test_pins[i] < MAX_TEST_PIN) {
				char text[20] = "";		// double max length - to be optimized
				strcpy(text, test_names[i]); // initial text
				strcat(text, "          ");		// pad
				text[10] = '\0';	// fix length
				showPinInfo(test_pins[i], text, header);
				header = false;
			}
		}
	}

}


#endif


 // use macros for test pins;
#if TEST_CASE==2

#include "utils.h"

void StartupMessage() {
	lst("\nPreprocessor directives; TestCase "); lst(TEST_CASE); Serial.print("\n\n");
	dpr("  Debug printing enabled"); dnl;
	lst("  Complier version: "); lst(__cplusplus); nl;
	lst("========================================\n\n");
}

void setup() {
	Serial.begin(115200);


	StartupMessage();

	SetupTestPins;

}

void loop() {
	ToggleSyncPin;
	SetTimingPin;

	for (long i = 1; i < 10; i++) {
		byte hp = i % 2;
		ToggleActivityPin;
	}

	ClearTimingPin;
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
