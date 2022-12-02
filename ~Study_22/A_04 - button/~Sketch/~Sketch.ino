

#define DBG

#define ACTIVITY_PIN 13		// 
#define TIMING_PIN 12		// 
#define SYNC_PIN 8			// 
#define PROBE_PIN 6 		// 
#define AUX_PIN 7 			// 


#include "..\@Utils\utils_test_pins.h"
//#include "utils.h"






void setup() {
	Serial.begin(115200);	Serial.print("\n");

	//dpr("Debug printing enabled"); dnl;

	SetupTestPins();

}

void loop() {

}
