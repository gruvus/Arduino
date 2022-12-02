#define DBG

//#define ACTIVITY_PIN 13			// green
#define TIMING_PIN 12				// red
#define SYNC_PIN 8					// blue
//#define PROBE_PIN 7 		
//#define AUX_PIN 6 			

#include "utils_test_pins.h"
#include "utils.h"


bool do_print = true;

void setup() {
	Serial.begin(115200);
	lst("\n  Bitwise Operations\n");
	lst("=====================================\n");

	dpr("  Debug printing enabled"); dnl;

	SetupTestPins;


	TimingLoop(Action_Nothing);

}

void loop() {
  
}

#define D 10

void TimingLoop(voidFuncPtr funcUnderTest) {

	funcUnderTest(); do_print = false;
	ulong delay_time = D;

	while (true) {
		ToggleSyncPin;
		//dlyMicros(D);
		delayMicroseconds(6);
		
		SetTimingPin;

		dlyMicros(D);
		
		//funcUnderTest();
		ClearTimingPin;
		
		delayMicroseconds(6);

	}
}
