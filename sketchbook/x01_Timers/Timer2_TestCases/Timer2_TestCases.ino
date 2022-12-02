
#include "T2_setup.h"
/*
*  Observable:
*  
* 	Comparator outputs: OC2A on pin 11 | OC2B on pin 3
* 
*  "probes" on pins 13 and 12 (PORTB5 and PORTB4):
*		overflow interrupt toggles pin 13
*		COMPA and COMPB interrupts set/clear pin 12
* 
*/

const byte NormalFix = 0;		//  0 to 255 fixed; can monitor with the A,B comparators
const byte NormalFix_AB = 1;	//  	above plus interrupts to generate pulse between A,B values;
const byte NormalVar = 2;		//  variable to 255; ovfl interrupt to preload; can monitor with the A,B comparators; toggle pin on overflow  
const byte NormalVar_AB = 3;	//		above plus interrupts to generate pulse between A,B values   
const byte CTC = 4;				//  0 to variable top (OCR2A); no interrupts; can monitor with the A(=top, fixed), B comparators
const byte CTC_AB = 5;			//		above plus interrupts to generate pulse between A,B values; no ovfl interrupt

const byte TestCase = NormalVar_AB;

const byte TestPinMode = 0;			// 0: A sets, B clears
//const byte TestPinMode = 1;			// 1: B sets, A clears


volatile byte counter_bottom = 0; // uint8_t

void run_test_case()
{
	// initialize timer2 
	noInterrupts();           // disable all interrupts
	TCCR2A = 0; 	TCCR2B = 0;		TIMSK2 = 0;

	// set interrupts
	switch (TestCase) {
	case  NormalVar:
		T2_set_intmask(0, 0, 1); // overflow only 
		break;
	case  NormalVar_AB:
		T2_set_intmask(1, 1, 1); // overflow and comparators A,B
		break;
	case  NormalFix:
		T2_set_intmask(0, 0, 0); // no interrupts 
		break;
	case  NormalFix_AB:
		T2_set_intmask(1, 1, 0); // comparators A,B
		break;
	case  CTC:
		T2_set_intmask(0, 0, 0); // no interrupts 
		break;
	case  CTC_AB:
		T2_set_intmask(1, 1, 0); // comparators A,B 
		break;
	default:
		T2_set_intmask(0, 0, 0); // no interrupts 
	}
	// set Waveform Generation Mode
	switch (TestCase) {
	case  CTC:
	case  CTC_AB:
		T2_set_wfgmode(T2_WGM_CTC);
		break;
	default:
		T2_set_wfgmode(T2_WGM_NORMAL);
	}
	// set Compare Output Mode
	T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
	T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3

	// set counting cycle/frequency
	byte div = 125, counter_top = 255;
	switch (TestCase) {

	case  NormalFix:
	case  NormalFix_AB:
		counter_bottom = 0; counter_top = 255;  // reflecting hw behavior, cannot change
		break;	// done NormalFix

	case  NormalVar:
	case  NormalVar_AB:
		counter_top = 255;					// reflecting hw behavior, cannot change
		counter_bottom = 255 - div + 1;		// load start value on overflow (at top)
		break;	// done NormalVar

	case  CTC:
	case  CTC_AB:
		counter_top = div - 1;
		OCR2A = counter_top;				// OCR2A sets TOP in CTC mode
		break;	// done CTC
	}
	{
		Serial.print("\nSet frequency\tBottom\tTop\tSteps");
		Serial.print("\n             \t");
		Serial.print(counter_bottom);	Serial.print("\t");
		Serial.print(counter_top);	Serial.print("\t");
		Serial.print(counter_top - counter_bottom + 1);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// set compare values
	int width = 0;
	switch (TestCase) {

	case  NormalFix:
	case  NormalFix_AB:
		OCR2A = counter_bottom + 1;	  // observe on pin 11
		OCR2B = counter_bottom + 0;	  // observe on pin 3 
		width = OCR2A - OCR2B;
		break;

	case  NormalVar:
	case  NormalVar_AB:
		OCR2A = counter_bottom + 2;	  // observe on pin 11
		OCR2B = counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		width = OCR2A - OCR2B;
		break;

	case  CTC:
	case  CTC_AB:
		OCR2B = 0;
		width = OCR2B + 1;

		break;
	}
	{
		Serial.print("\nSet A,B\t\tA\tB\tWidth");
		Serial.print("\n       \t\t");
		Serial.print(OCR2B);	Serial.print("\t");
		Serial.print(OCR2A);	Serial.print("\t");
		Serial.print(width);	Serial.print("\t");
		Serial.print("\n\n");
	}

	// get ready
	TCNT2 = counter_bottom;   // preload counter

	// set prescaler and start the counter
	T2_set_prescaler(T2_PSCALE_64); // PSCALE_1,8,32,64,128,256,1024

	interrupts();             // enable all interrupts

	// can observe OC2A/B on pins 11/3

	pinMode(11, OUTPUT);	// OC2A
	pinMode(3, OUTPUT);		// OC2B

}

void StartupMessage() {
	bool invalid_case = false;
	Serial.print("Test Case:\t"); Serial.print(TestCase); Serial.print("\t");
	switch (TestCase) {
	default:
		Serial.print("Undefined\n\n\t*** Stopped ***\n");
		invalid_case = true;
		break;

	case  NormalFix:	Serial.print("NormalFix");		break;
	case  NormalFix_AB:	Serial.print("NormalFix_AB");	break;
	case  NormalVar:	Serial.print("NormalVar");		break;
	case  NormalVar_AB:	Serial.print("NormalVar_AB");	break;
	case  CTC_AB:		Serial.print("CTC_AB");			break;
	case  CTC:			Serial.print("CTC");			break;
	}

	while (invalid_case) {} // stop here

	Serial.print("\n========================================\n");

}

void setup()
{
	pinMode(13, OUTPUT);		// built-in LED  //pin 13: PORTB5 PINB5
	pinMode(12, OUTPUT);		// "probe" pin   //pin 12: PORTB4 PINB4

	Serial.begin(115200);	Serial.print("\n");
	StartupMessage();

	run_test_case();
}

void loop() {}

ISR(TIMER2_OVF_vect) {
	PINB |= (1 << PINB5); // fast toggle pin 13 built-in LED
	TCNT2 = counter_bottom;   // reload counter 
}

ISR(TIMER2_COMPA_vect) {
	if (TestPinMode == 1)
		PORTB &= ~(1 << PORTB4);	// clear bit
	else
		PORTB |= (1 << PORTB4);		// set bit
}

ISR(TIMER2_COMPB_vect) {

	if (TestPinMode == 1)
		PORTB |= (1 << PORTB4);		// set bit
	else
		PORTB &= ~(1 << PORTB4);	// clear bit


}


