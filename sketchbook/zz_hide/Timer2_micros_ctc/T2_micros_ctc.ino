#define DBG
#include "..\@Utils\utils.h"

/* these ar in Arduino.h
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

*/

const float F_CPU_MHz = F_CPU / 1000000.0;	// same value as "clockCyclesPerMicrosecond

// configuration

#define T2_DIV 250					// count cycle / divisor
#define RESOLUTION 1 //  4, 2, 0.5 microseconds

#if (RESOLUTION == 4)
T2_pscale PSCALE = T2_PSCALE_64;	// PSCALE_1,8,32,64,128,256,1024
#define PSCALE_FACTOR 64
#define MILLIS_BASE 0 
#define MICROS_BASE 1192

#elif (RESOLUTION == 2)
T2_pscale PSCALE = T2_PSCALE_32;	// PSCALE_1,8,32,64,128,256,1024
#define PSCALE_FACTOR 32
#define MILLIS_BASE 1   
#define MICROS_BASE 1408

#elif (RESOLUTION == 1)
T2_pscale PSCALE = T2_PSCALE_8;	// PSCALE_1,8,32,64,128,256,1024
#define PSCALE_FACTOR 8
#define MILLIS_BASE 0   
#define MICROS_BASE 1570

#endif

#define T2_TPCLK PSCALE_FACTOR / F_CPU_MHz			// prescaled clock period in microseconds = prescale_factor * 1/16Mhz
#define T2_TCYCLE T2_TPCLK * T2_DIV	


//unsigned int ovflag_count = 0; // see micros2() function


static byte pscale_N = 0;


void SetupTimer2() {
	// initialize timer2 
	
	pscale_N = T2_prescale_factor(PSCALE);

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
	//byte div = 250;			// with prescaler :64 -> 16MHz/64/250 = 1kHz
	byte div = T2_DIV;			// with prescaler :128 -> 16MHz/128/125 = 1kHz
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



void TestPrint() {

	Serial.print("<TestPrint>"); Serial.print("\n");

	Serial.print("\t");
	Serial.print("Pre-scaled clock period (us)\t"); Serial.print(T2_TPCLK); 	Serial.print("\n");
	Serial.print("\t");
	Serial.print("Prescale number\t"); Serial.print(pscale_N);			Serial.print("\n");
	Serial.print("\t");
	Serial.print("Prescale factor\t"); Serial.print(PSCALE_FACTOR);		Serial.print("\n");
	Serial.print("\t");
	Serial.print("T2_TPCLK\t"); Serial.print(T2_TPCLK);		Serial.print("\n");
	Serial.print("\n");
}


volatile unsigned long timer2_overflow_count = 0;
volatile unsigned long timer2_millis = MILLIS_BASE;  // 7 * prescale value


unsigned long millis2()
{
	unsigned long m;
	
	uint8_t oldSREG = SREG;
	cli();  // disable interrupts
	
	m = timer2_millis;		// pScale, div 64/250 or 128/125 
	
	switch (pscale_N) {
	case 32:	m = timer2_millis >> 1; break; // 32/250
	case 8:		m = timer2_millis >> 3; break; // 8/250
	case 1:		m = timer2_millis >> 6;  break;// 1/250
	}

	SREG = oldSREG;  // restore interrupts
	return m;
}


unsigned long micros2() {

	const float tpclk = pscale_N/float(F_CPU_MHz); //


	uint8_t oldSREG = SREG;  // save state
	cli();		// disable interrupts

	unsigned long t = TCNT2;
	unsigned long m = timer2_overflow_count * T2_DIV;

	SREG = oldSREG;	// restore state (also enables interrupts after the next instruction)

	
	//{
	//	dpr("ovfl"); dtb; dpr(timer2_overflow_count); dnl;
	//	dpr("t"); dtb; dpr(t); dnl;
	//	dpr("T2_DIV"); dtb; dpr(T2_DIV); dnl;
	//	dpr("m"); dtb; dpr(m); dnl;
	//	dpr("m + t"); dtb; dpr(m + t); dnl;
	//	dpr("tpclk"); dtb; dpr(tpclk); dnl;
	//	dpr("T2_TPCLK"); dtb; dpr(T2_TPCLK); dnl;
	//	unsigned long r = (m + t)* tpclk; // *T2_TPCLK;
	//	dpr("r"); dtb; dpr(r); dnl;
	//	//unsigned long p = (m + t) * T2_TPCLK; // *T2_TPCLK; // wrong reslt(why?)
	//	//dpr("p"); dtb; dpr(p); dnl;
	//	dnl;
	//}
	
	
	return (m + t) * tpclk + MICROS_BASE;
}


ISR(TIMER2_COMPA_vect) {

	PORTB |= (1 << PORT4); // set pin 12
	//.........................................................................

	timer2_millis++;
	
	timer2_overflow_count++;

	//.........................................................................
	PORTB &= ~(1 << PORT4); // clear pin 12

//	PINB |= (1 << PINB4); // toggle pin 12

}

//ISR(TIMER2_COMPB_vect) {
//
//}






