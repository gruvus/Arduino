
#include "T_OneShot_16bit.h"


//--------------------------------------------------------------
OneShot16::OneShot16()
	: OneShotBase(hwspec16)  // pass the hw specs to the base
{
}

/*

//--------------------------------------------------------------
 void OneShot16::show_regs() const  {

	dtb; dpr("OCR1A"); dtb; dpr(OCR1A);
	dtb; dpr("OCR1B"); dtb; dpr(OCR1B);
	dtb; dpr("width = "); dpr(OCR1A - OCR1B);  dnl;
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> 

OneShot16 myOneShot16_onT1; // create one global instance  // Serial is not open yet

//--------------------------------------------------------------
#ifndef HIDE_ISR
ISR(TIMER1_OVF_vect) {
	myOneShot16_onT1.ActionCall();
}

ISR(TIMER1_COMPA_vect) { Action_Nothing ; }

ISR(TIMER1_COMPB_vect) { Action_Nothing; }

// EMPTY_INTERRUPT(TIMER1_COMPB_vect);

 #endif


*/

