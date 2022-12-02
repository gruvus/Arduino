
//#define HIDE_ISR

/* uses test pins
TIMING_PIN	in ISR(TIMER2_OVF_vect)
PROBE_PIN	in ISR(TIMER2_COMPA_vect) and SR(TIMER2_COMPB_vect)
*/


#include "T_OneShot_8bit.h"


//--------------------------------------------------------------
OneShot8::OneShot8()
	: OneShotBase(hwspec8)  // pass the hw specs to the base
{
}


//--------------------------------------------------------------
void OneShot8::show_regs() const {

	dtb; dpr("OCR2A"); dtb; dpr(OCR2A);
	dtb; dpr("OCR2B  "); dtb; dpr(OCR2B);
	dtb; dpr("width = "); dpr(OCR2A - OCR2B);  dnl;

}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> 

OneShot8 myOneShot8_onT2; // create one global instance  // Serial is not open yet

//--------------------------------------------------------------
#ifndef HIDE_ISR
ISR(TIMER2_OVF_vect) {
	myOneShot8_onT2.ActionCall();
}

ISR(TIMER2_COMPA_vect) { Action_Nothing; }

ISR(TIMER2_COMPB_vect) { Action_Nothing; }

#endif

#if 0
--------------------------------------------------------------
void OneShot8::_ConfigureHardware_v1()
{
	// initialize hw Timer1 in NormalVar mode; generates overflow interrupt at TOP 
	{
		noInterrupts();           // disable all interrupts, clear control registers
		TCCR2A = 0; 	TCCR2B = 0;		TIMSK2 = 0;
		// set interrupts: overflow,  A,B only for test
		T2_set_intmask(1, 1, 1);
		// set Waveform Generation Mode
		T2_set_wfgmode(T2_WGM_NORMAL);
		// set Compare Output Mode
		T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
		T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3
	}

	// for observation, may not need in applictions, should be able to exclude
	{
		// can observe OC2A/B on pins 11/3
		pinMode(11, OUTPUT);		// OC1A
		pinMode(3, OUTPUT);			// OC1B

		SetupTestPins; // uses test pins
	}

	// get ready

	Stop();			// hold the clock, do not start yet
	//	Reset();		// TCNT2 = counter_bottom;		// preload counter 
	interrupts();   // enable interrupts

	// ready to go

}

#endif