#ifdef ARDUINO_AVR_MEGA2560

#include "g_OneShot16_onT5.h"

#define HWTIMER 5	// select hw counter to use
#include "GenT16.h" // general hw specific setup for 16bit counters

const char who[] = "<OneShot16_onT5::";

void OneShot16_onT5::Stop() { SetPrescaler_16(0); }		// stop the clock
void OneShot16_onT5::Run() { SetPrescaler_16(pscale_id); }		// run the clock}
void OneShot16_onT5::Reset() { TCNTn = counter_bottom; }
void OneShot16_onT5::ClrRegs() { ClearControlRegisters_16(); }

void OneShot16_onT5::_Config_InterruptMask(byte ovf, byte oc_A, byte oc_B, byte oc_C) {
	// set interrupts: overflow,  A,B only for test
	SetIntMask_16(ovf, oc_A, oc_B, oc_C);
};

void OneShot16_onT5::_Config_WGFmode(const byte comp_mode_id) {
	// set Waveform Generation Mode
	SetWFGmode_16(comp_mode_id);	// need enum !
};

void OneShot16_onT5::_Config_Compares(byte modeA, byte modeB, byte modeC) {

	SetCompA_16(modeA);
	SetCompB_16(modeB);
	SetCompC_16(modeC);
};

void OneShot16_onT5::setOCRegs(uint16_t Aval, uint16_t Bval, uint16_t Cval, uint16_t Dval) {

	dpr(who); dpr("setOCRegs> "); dpr(Aval); dtb; dpr(Bval); dtb; dpr(Cval); dnl;

	setOCRegs_16(Aval, Bval, Cval, Dval);
}

void OneShot16_onT5::showOCRegs() const { showOCRegs_16(HWTIMER); }


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> 

OneShot16_onT5 myOneShot16_onT5; // create one global instance 

//--------------------------------------------------------------
ISR(TIMERn_OVF_vect) {
	myOneShot16_onT5.ActionCall();
}

ISR(TIMERn_COMPA_vect) { Action_Nothing; }

ISR(TIMERn_COMPB_vect) { Action_Nothing; }

#endif
