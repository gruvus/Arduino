/*
* setup a regular interval event (interrupt)
* attach handler
*
* use Timer2

*/


#include "T2_setup.h"



T2_pscale PSCALE = T2_PSCALE_64;	// PSCALE_1,8,32,64,128,256,1024

static byte pscale_N = 0;

volatile unsigned long event_count = 0;


void SetupEventTimer() {
	// initialize timer2 in CTC mode at 1kHz
	// generates "top count" interrupt on OCR2A 


	noInterrupts();           // disable all interrupts
	TCCR2A = 0; 	TCCR2B = 0;		TIMSK1 = 0;

	// set interrupts
	T2_set_intmask(1, 0, 0); // comparators A,B (only for test) 

	// set Waveform Generation Mode
	T2_set_wfgmode(T2_WGM_CTC);
	// set Compare Output Mode
	T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
	T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3

	// set counting cycle/frequency
	byte counter_bottom = 0; // fixed in CTC mode
	byte div = 250;			// with prescaler :64 -> 16MHz/64/250 = 1kHz
	//byte div = 125;			// with prescaler :128 -> 16MHz/128/125 = 1kHz
	byte counter_top = div - 1;		// for convenience
	OCR2A = counter_top;			// OCR2A sets TOP in CTC mode

	{
		Serial.print("\n\tSet frequency\tBottom\tTop\tSteps");
		Serial.print("\n\t             \t");
		Serial.print(counter_bottom);	Serial.print("\t");
		Serial.print(counter_top);	Serial.print("\t");
		Serial.print(counter_top - counter_bottom + 1);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// set compare values
	byte width = 1;
	OCR2B = width - 1;

	{
		Serial.print("\n\tSet A,B\t\tA\tB\tWidth");
		Serial.print("\n\t       \t\t");
		Serial.print(OCR2B);	Serial.print("\t");
		Serial.print(OCR2A);	Serial.print("\t");
		Serial.print(width);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// set prescaler and start the counter
	T2_set_prescaler(PSCALE); // PSCALE_1,8,32,64,128,256,1024

	interrupts();             // enable all interrupts

	// can observe OC2A/B on pins 11/3

	pinMode(11, OUTPUT);	// OC2A
	pinMode(3, OUTPUT);		// OC2B
}

unsigned long start_time = 0;

typedef void (*voidFuncPtr)(void);

static volatile voidFuncPtr dynamic_handler;

void setup()
{
	// test pins
	pinMode(13, OUTPUT);		// built-in LED  //pin 13: PORTB5 PINB5
	pinMode(12, OUTPUT);		// "probe" pin   //pin 12: PORTB4 PINB4

	Serial.begin(115200);	Serial.print("\n");

	StartupMessage();

	pscale_N = T2_prescale_factor(PSCALE);

	//dynamic_handler = event_handler_1;  // register handler

	start_time = millis();

	SetupEventTimer();

	dynamic_handler = event_handler_1;  // register handler


}

void StartupMessage() {

	Serial.print(" Timer Events Execise\t");
	Serial.print("\n ========================================\n");
	Serial.print("   Using Timer2 \n");

}


const byte N = 33;


void loop()
{
	static int i = 0; static byte pass = 0;
	unsigned long dt = millis() - start_time;

	if (i == 0) {
		Serial.print("\n");
		Serial.print("\t");	Serial.print("i");
		Serial.print("\t");	Serial.print("N");
		Serial.print("\t");	Serial.print("dt");
		Serial.print("\t"); Serial.print("ev_cnt");
		Serial.print("\t"); Serial.print("dt/N");
		Serial.print("\t"); Serial.print("dif");
		Serial.print("\t"); Serial.print("ratio");
		Serial.print("\n");

		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\t");	Serial.print("=======");
		Serial.print("\n");
	}

	if ((pass < 2) && (i < 20)) {

		Serial.print("\t");	Serial.print(i);
		Serial.print("\t");	Serial.print(N);
		Serial.print("\t");	Serial.print(dt);
		Serial.print("\t"); Serial.print(event_count);
		Serial.print("\t"); Serial.print(dt / N);
		Serial.print("\t"); Serial.print(event_count - dt / N);
		Serial.print("\t"); Serial.print(event_count/(dt / N));

		Serial.print("\n");
		i++;
		if (i >= 20) {
			noInterrupts();
			pass++; i = 0; start_time = millis(); event_count = 0;
			// change handler
			dynamic_handler = event_handler_2;
			interrupts();
		}

	delay(100);
	}

	while (pass > 1) {
		// stop here
	}

}


void event_handler_1() {

	event_count++;

}

void event_handler_2() {

	event_count++;
	event_count++;
	event_count++;

}


ISR(TIMER2_COMPA_vect) {

	PORTB |= (1 << PORTB4); // set pin 12

	static byte k = 0;
	//.........................................................................
	k++;
	k %= N;
	if (k == 0) {
		// call every N ticks (ms)
		//event_handler();
		dynamic_handler(); 
	}


	//.........................................................................
	PORTB &= ~(1 << PORTB4); // clear pin 12

	//	PINB |= (1 << PINB4); // toggle pin 12

}

