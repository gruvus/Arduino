
// utils_test_pins.h

#ifndef _utils_test_pins_h
#define _utils_test_pins_h

#include "arduino.h"


//***************************************************
#define MAX_TEST_PIN 100

#ifdef ARDUINO_AVR_UNO
#include "utils_test_pins_UNO.h"
#endif

#ifdef ARDUINO_AVR_MEGA2560
#include "utils_test_pins_MEGA.h"

#endif


//***************************************************************************
//*** checks for duplicate use **********************************************

#if ACTIVITY_PIN==TIMING_PIN
#error Invalid ACTIVITY_PIN==TIMING_PIN number 
#endif
#if TIMING_PIN==SYNC_PIN
#error Invalid TIMING_PIN==SYNC_PIN number 
#endif
#if SYNC_PIN==PROBE_PIN
#error Invalid SYNC_PIN==PROBE_PIN number 
#endif
#if PROBE_PIN==AUX_PIN
#error Invalid PROBE_PIN==AUX_PIN number 
#endif
#if AUX_PIN==ACTIVITY_PIN
#error Invalid AUX_PIN==ACTIVITY_PIN number 
#endif

#if ACTIVITY_PIN==SYNC_PIN
#error Invalid ACTIVITY_PIN==SYNC_PIN number 
#endif
#if SYNC_PIN==AUX_PIN
#error Invalid SYNC_PIN==AUX_PIN number 
#endif
#if AUX_PIN==TIMING_PIN
#error Invalid AUX_PIN==TIMING_PIN number 
#endif
#if TIMING_PIN==PROBE_PIN
#error Invalid TIMING_PIN==PROBE_PIN number 
#endif
#if PROBE_PIN==ACTIVITY_PIN
#error Invalid PROBE_PIN==ACTIVITY_PIN number 
#endif


//*** setup functions ***************************************************

#define _showPin(m,p) \
Serial.print((m));\
if((p) < 100) Serial.println((p)); else  Serial.println("-");

#if (defined ACTIVITY_PIN) & (ACTIVITY_PIN < MAX_TEST_PIN)
#define _SetActivityMode pinMode(activity_pin, OUTPUT);\
_showPin("\tActivity: ", activity_pin)

#else 
#define _SetActivityMode
#endif

#if (defined TIMING_PIN) & (TIMING_PIN < MAX_TEST_PIN)
#define _SetTimingMode pinMode(timing_pin, OUTPUT);\
_showPin("\tTiming:\t  ", timing_pin)

#else 
#define _SetTimingMode
#endif

#if (defined SYNC_PIN) & (SYNC_PIN < MAX_TEST_PIN)
#define _SetSyncMode pinMode(sync_pin, OUTPUT);\
_showPin("\tSync:\t  ", sync_pin)

#else 
#define _SetSyncMode
#endif

#if (defined PROBE_PIN) & (PROBE_PIN < MAX_TEST_PIN)
#define _SetProbeMode pinMode(probe_pin, OUTPUT);\
_showPin("\tProbe:\t  ", probe_pin)

#else 
#define _SetProbeMode
#endif

#if (defined AUX_PIN) & (AUX_PIN < MAX_TEST_PIN)
#define _SetAuxMode pinMode(aux_pin, OUTPUT);\
_showPin("\tAux:\t  ", aux_pin)

#else 
#define _SetAuxMode
#endif

//***************************************************

#define ActivityPinName "Activity"
#define TimingPinName "Timing"
#define SyncPinName "Sync"
#define ProbePinName "Probe"
#define AuxPinName "Aux"

//***************************************************

#define SetupTestPins   \
Serial.print("\nTest pins:\n");\
_SetActivityMode  _SetTimingMode _SetSyncMode _SetProbeMode _SetAuxMode ;\
Serial.print("\n");\
showTestPinsInfo();


//***************************************************

#include "utils.h"

static void showTestPinsInfo() {

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
	dnl;
	Serial.flush();
}









#endif // #ifndef _utils_test_pins_h
