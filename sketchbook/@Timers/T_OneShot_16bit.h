// T_OneShot_16bit.h
#pragma once

#include "T_OneShot_Base.h"
//#include "T1_setup.h"


class OneShot16 :public OneShotBase
{
	// ********* methods **********
public: 
	OneShot16();  // constructor	

	//void Stop() { T1_set_prescaler(T1_PSCALE_0); }		// stop the clock
	//void Run() { T1_set_prescaler(T1_pscale_id(pscale_id)); };		// run the clock}
	//void Reset() { TCNT1 = counter_bottom; };

	//void show_regs() const;

private:



};

/*

	void _Config_ClearCtrlRegs() {
		TCCR1A = 0; 	TCCR1B = 0;		TIMSK1 = 0;
	};

	void _Config_InterruptMask() {
		// set interrupts: overflow,  A,B only for test
		T1_set_intmask(0, 0, 1);
	};

	void _Config_WGFmode() {
		// set Waveform Generation Mode
		T1_set_wfgmode(T1_WGM_NORMAL);
	};

	void _Config_Compares() {

		T1_set_comA(T1_COM_TOGGLE);	// observe OC1A on pin 9
		T1_set_comB(T1_COM_TOGGLE);	// observe OC1B on pin 10

		// can observe OC1A/B on pins 9/10
		pinMode(9, OUTPUT);		// OC1A
		pinMode(10, OUTPUT);	// OC1B
	};




*/




//extern OneShot16 myOneShot16_onT1;


