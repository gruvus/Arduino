
#define ACTIVITY_PIN 13			// green
#define TIMING_PIN 12				// red
#define SYNC_PIN 8					// blue
#define PROBE_PIN 7 		
#define AUX_PIN 6 			

#include "utils_test_pins.h"


void setup() {

}

void loop() {
  
}


void TimingLoop() {

	volatile float a = 2, b = 3, c = 0, d = 0;

	while (micros()) {
		ToggleSyncPin;
		//dlyMicros(5);
		//a=-a;
		SetTimingPin;
		{
			//c = a / b;
			c = round(a / b);
			//d = c;
		}
		ClearTimingPin;

		dlyMicros(5);

	}

}
