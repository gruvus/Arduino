// T_OneShot_8bit.h
#pragma once

#include "T_OneShot_Base.h"
#include "T2_setup.h"





class OneShot8:public OneShotBase
{

public:	// ********* methods **********

	OneShot8();

	void Stop()  { T2_set_prescaler(T2_PSCALE_0); }				// stop the clock
	void Run()   { T2_set_prescaler(T2_pscale(pscale_id)); };	// run the clock}
	void Reset() { TCNT2 = counter_bottom; };

	void show_regs() const;

private:

	void _Config_ClearCtrlRegs() {
		// clear control registers
		TCCR2A = 0; 	TCCR2B = 0;		TIMSK2 = 0;
	};

	void _Config_InterruptMask(byte ovf, byte oc_A, byte oc_B, byte oc_C) {
		// set interrupts: overflow,  A,B only for test
		T2_set_intmask(1, 1, 1);
	};

	void _Config_WGFmode(const byte comp_mode_id) {
		// set Waveform Generation Mode
		T2_set_wfgmode(T2_WGM_NORMAL);
	};

	void _Config_Compares(byte modeA, byte modeB, byte modeC) {
		// set Compare Output Mode
		T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
		T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3

		// can observe OC2A/B on pins 11/3
		pinMode(11, OUTPUT);		// OC1A
		pinMode(3, OUTPUT);			// OC1B
	};

};

extern OneShot8 myOneShot8_onT2;

	//void _ConfigureHardware_v1();
