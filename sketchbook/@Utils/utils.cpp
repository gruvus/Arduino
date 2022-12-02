
#include "utils.h"


void Action_Nothing() {}


void dlyMicros(ulong delay_time) {

	if (delay_time < 5)
		delayMicroseconds(delay_time+1);
	
	else {
		ulong start_time = micros(); // +delay_time; // adds ~0.5 - 0.6 us
		//stop_time += delay_time;
		while (micros() - start_time < delay_time) {}	// delay
	}
}



