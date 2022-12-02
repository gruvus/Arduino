/*
* Micros/Millis function with Timer2
*
*/

#include "T2_setup.h"

void Action_Nothing() {}


unsigned int ovflag_count = 0;


void SetupTimer2() {
	// initialize timer2 
	noInterrupts();           // disable all interrupts
	TCCR2A = 0; 	TCCR2B = 0;		TIMSK1 = 0;

	// set interrupts
	T2_set_intmask(0, 0, 1); // comparators A,B, overflow
	// set Waveform Generation Mode
	T2_set_wfgmode(T2_WGM_NORMAL);
	// set Compare Output Mode
	T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
	T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3

	// set counting cycle/frequency
	// is fixed in Normal mode
	byte counter_bottom = 0, counter_top = 255;
	{
		Serial.print("\nSet frequency\tBottom\tTop\tSteps");
		Serial.print("\n             \t");
		Serial.print(counter_bottom);	Serial.print("\t");
		Serial.print(counter_top);	Serial.print("\t");
		Serial.print(counter_top - counter_bottom + 1);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// set compare values // only for checking the timer setup
	byte width = 128;
	OCR2B = counter_bottom + 64;
	OCR2A = OCR2B + width;

	{
		Serial.print("\nSet A,B\t\tA\tB\tWidth");
		Serial.print("\n       \t\t");
		Serial.print(OCR2B);	Serial.print("\t");
		Serial.print(OCR2A);	Serial.print("\t");
		Serial.print(width);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// set prescaler and start the counter
	T2_set_prescaler(T2_PSCALE_64); // PSCALE_1,8,32,64,128,256,1024

	interrupts();             // enable all interrupts

	// can observe OC2A/B on pins 11/3

	pinMode(11, OUTPUT);	// OC2A
	pinMode(3, OUTPUT);		// OC2B
}


void run_millis() {
	for (int i = 0; i < 20; i++) {
		long m = millis(), m2 = millis2();
		Serial.print(m); Serial.print("\t"); Serial.print(m2); Serial.print("\t"); Serial.print(m2 - m);
		Serial.print("\n");

		delay(100);
	}
	Serial.print("\n");

}

void run_micros() {
	for (int i = 0; i < 40; i++) {
		long m = micros(), m2 = micros2();
		Serial.print(m); Serial.print("\t"); Serial.print(m2); Serial.print("\t"); Serial.print(m2 - m);
		Serial.print("\n");

		delay(100);
	}

	Serial.print("\n");
	Serial.print("ovflag_count:\t"); Serial.print(ovflag_count);
	Serial.print("\n");


}



void setup() {
	pinMode(13, OUTPUT);		// built-in LED  //pin 13: PORTB5 PINB5
	pinMode(12, OUTPUT);		// "probe" pin   //pin 12: PORTB4 PINB4

	Serial.begin(115200);	Serial.print("\n");
	StartupMessage();
	SetupTimer2();

	run_millis();

	run_micros();

}


void loop() {

}





