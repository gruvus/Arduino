/*
* Micros/Millis function with Timer2 in CTC mode
*
*/

#include "T2_setup.h"

extern byte pscale_N;

extern volatile unsigned long timer2_overflow_count;

void Action_Nothing() {}


void setup() {
	pinMode(13, OUTPUT);		// built-in LED  //pin 13: PORTB5 PINB5
	pinMode(12, OUTPUT);		// "probe" pin   //pin 12: PORTB4 PINB4

	Serial.begin(115200);	Serial.print("\n");

	StartupMessage();

	SetupTimer2();

	TestPrint();


	run_millis();
	delay(1000);
	run_micros();
}

void StartupMessage() {

	Serial.print(" MicrosAlt\t");
	Serial.print("\n ========================================\n");
}

void run_millis() {
	for (int i = 0; i < 10; i++) {
		unsigned long m = millis(), m2 = millis2();
		Serial.print(m); Serial.print("\t"); Serial.print(m2); Serial.print("\t"); Serial.print(int(m2 - m));
		Serial.print("\n");

		delay(50);
	}
	Serial.print("\n");
}

void run_micros() {
	for (int i = 0; i < 10; i++) {
		unsigned long m = micros(), m2 = micros2();
		Serial.print(m); Serial.print("\t"); Serial.print(m2); Serial.print("\t"); Serial.print(int(m2 - m));
		Serial.print("\n");

		delay(10);
	}

	Serial.print("\n");
	Serial.print("ovflag_count:\t"); Serial.print(timer2_overflow_count);
	Serial.print("\n");


}




void loop() {
	int r = rand() / (RAND_MAX/ 100);
	// int r = rand();
	unsigned long dly = 10000 + r;
	unsigned long m = micros(), m2 = micros2();
	Serial.print(m); Serial.print("\t"); Serial.print(m2); Serial.print("\t"); Serial.print(int(m2 - m));
	Serial.print("\t"); Serial.print(dly);
	Serial.print("\t"); Serial.print((float)round((timer2_overflow_count*1.0)/ pscale_N /1000));
	Serial.print("\t"); Serial.print(timer2_overflow_count);

	Serial.print("\n");
	delay(dly);

}