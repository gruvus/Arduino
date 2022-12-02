/*
*  Observable:
*
* 	Comparator outputs: OC1A on pin 9 | OC1B on pin 10
*
*  "probes" on pins 13 and 12:
*	Activity:	overflow interrupt toggles pin 13
*	Timing pin:	COMPA and COMPB interrupts set/clear pin 12
*
*/

#define DBG

//#define ACTIVITY_PIN 13
#define TIMING_PIN 12
#define SYNC_PIN 8
//#define PROBE_PIN 7

#include "utils_test_pins.h"
//#include "utils.h"
#include "T1_setup.h"
#include "T1_aux.h"

const byte NormalFix = 0;		//  0 to 65535 fixed; can monitor with the A,B comparators
const byte NormalFix_AB = 1;	//  	above plus interrupts to generate pulse between A,B values;
const byte NormalVar = 2;		//  variable to 65535; ovfl interrupt to preload; can monitor with the A,B comparators; toggle pin on overflow  
const byte NormalVar_AB = 3;	//		above plus interrupts to generate pulse between A,B values   
const byte CTC = 4;				//  0 to variable top (OCR1A); no interrupts; can monitor with the A(=top, fixed), B comparators
const byte CTC_AB = 5;			//		above plus interrupts to generate pulse between A,B values; no ovfl interrupt

const byte TestCase = CTC_AB;

//const byte TestPinMode = 0;			// 0: A sets, B clears
const byte TestPinMode = 1;			// 1: B sets, A clears

myT1_t myT;



void run_test_case()
{
	// initialize timer1 
	myT.counter_bottom = 0;
	myT.call_count = 0;
	myT.event_handler = Action_Nothing;


	noInterrupts();           // disable all interrupts
	TCCR1A = 0; 	TCCR1B = 0;		TIMSK1 = 0; // clear control registers

	// set interrupts
	switch (TestCase) {
	case  NormalVar:
		T1_set_intmask(0, 0, 1); // overflow only 
		break;
	case  NormalVar_AB:
		T1_set_intmask(1, 1, 1); // overflow and comparators A,B
		break;
	case  NormalFix:
		T1_set_intmask(0, 0, 0); // no interrupts 
		break;
	case  NormalFix_AB:
		T1_set_intmask(1, 1, 0); // comparators A,B
		break;
	case  CTC:
		T1_set_intmask(0, 0, 0); // no interrupts 
		break;
	case  CTC_AB:
		T1_set_intmask(1, 1, 0); // comparators A,B 
		break;
	default:
		T1_set_intmask(0, 0, 0); // no interrupts 
	}
	// set Waveform Generation Mode
	switch (TestCase) {
	case  CTC:
	case  CTC_AB:
		T1_set_wfgmode(T1_WGM_CTC);
		break;
	default:
		T1_set_wfgmode(T1_WGM_NORMAL);
	}
	// set Compare Output Mode
	T1_set_comA(T1_COM_TOGGLE);	// observe OC1A on pin 9
	T1_set_comB(T1_COM_TOGGLE);	// observe OC1B on pin 10

	// **********  set counting cycle/frequency and compare values *********

	myT.div = UMAX16 + 1;


	switch (TestCase) {
	case  NormalFix:
	case  NormalFix_AB:
	{
		myT.counter_bottom = 0; myT.counter_top = UMAX16;  // reflecting hw behavior, cannot change
		OCR1A = 0x7FFF;	  // observe on pin 9
		OCR1B = 0x6FFF;	  // observe on pin 10 
		break;	// done NormalFix
	}
	//..............................
	case  NormalVar:
	case  NormalVar_AB:
	{
		myT.counter_top = UMAX16;					// reflect hw behavior, cannot change
		myT.div = UMAX16 + 1;						// division factor; max 65536
		myT.div = 1;
		myT.counter_bottom = UMAX16 - myT.div + 1;		// load start value on overflow (at top); controls cycle

		OCR1A = myT.counter_top;
		OCR1B = (0L + myT.counter_bottom + myT.counter_top) / 2;
		//		OCR1B = 0;	// try values from 0 up to check delay until preload

				//OCR1A = counter_bottom + 2;	  // observe on pin 9
				//OCR1B = counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled

		break;	// done NormalVar
	}
	//..............................
	case  CTC:
	case  CTC_AB:
	{
		myT.counter_bottom = 0;		// hw behavior, cannot change

		// cycle time = myT.div * pscale clock period

		//float ptck = T1_prescale_factor(myT.PSCALE) / (F_CPU / 1000000.0); // micros
		
		const float T = 0.100; // desired millis

		//FindFactors(0.3333);
		BestFactors(T);


		myT.counter_top = myT.div - 1;		// parameter

		// OCR1A sets TOP in CTC mode, controls cycle
		OCR1A = myT.counter_top;
		OCR1B = OCR1A / 2;	  // observe on pin 10 
		break;	// done CTC
	}

	} //switch (TestCase)


	{
		Serial.print("\nSet frequency\tBottom\tTop\tSteps");
		Serial.print("\n             \t");
		Serial.print(myT.counter_bottom);	Serial.print("\t");
		Serial.print(myT.counter_top);	Serial.print("\t");
		Serial.print(myT.counter_top - myT.counter_bottom + 1L);	Serial.print("\t");
		Serial.print("\n\n");
	}
	{
		uint16_t width = OCR1A - OCR1B;		// width of pulse generated on probe pin
		Serial.print("\nSet A,B\t\tB\tA\tWidth");
		Serial.print("\n       \t\t");
		Serial.print(OCR1B);	Serial.print("\t");
		Serial.print(OCR1A);	Serial.print("\t");
		Serial.print(width);	Serial.print("\t");
		Serial.print("\n\n");
	}

	//ShowConfig_T1("in run_test_case, after setting compare registers");

	// get ready
	TCNT1 = myT.counter_bottom;   // preload counter 

	// set prescaler and start the counter
	T1_set_prescaler(myT.PSCALE); // PSCALE_1,8,64,256,1024

	ShowConfig_T1("in run_test_case, after T1_set_prescaler");

	interrupts();             // enable all interrupts

	// can observe OC2A/B on pins 11/3

	pinMode(9, OUTPUT);		// OC1A
	pinMode(10, OUTPUT);		// OC1B

}

void StartupMessage() {
	bool invalid_case = false;
	Serial.print("\nRunning Timer 1 (16bit) Test Cases \n");
	Serial.print("\n========================================\n");

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

	Serial.begin(115200);	Serial.print("\n");
	StartupMessage();

	dpr("Debug printing enabled"); dnl;
	SetupTestPins;

	//printBits((unsigned int)23);
	//showPinInfo(timing_pin, 1);


	//ShowConfig_T1("after startup");

	run_test_case();


	//ShowConfig_T1("after run_test_case");

}

void loop() {}

ISR(TIMER1_OVF_vect) {
	if (TestCase != CTC_AB)
		ToggleSyncPin; // there's no overflow interrupt in CTC mode; OC1A is equv in CTC mode

	TCNT1 = myT.counter_bottom;   // reload counter initial value 
}

ISR(TIMER1_COMPA_vect) {
	if (TestCase == CTC_AB)		// there's no overflow interrupt; OC1A is equv in CTC mode
		ToggleSyncPin;


	if (TestPinMode == 1)
		ClearTimingPin;
	else
		SetTimingPin;
}

ISR(TIMER1_COMPB_vect) {

	if (TestPinMode == 1)
		SetTimingPin;

	else
		ClearTimingPin;


}


