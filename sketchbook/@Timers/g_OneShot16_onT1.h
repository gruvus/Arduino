// g_OneShot16_onT1.h
#pragma once

#include "T_OneShot_16bit.h"

class OneShot16_onT1 : public OneShot16
{
public:

	void Stop();		// stop the clock
	void Run();		// run the clock}
	void Reset();
	void ClrRegs();

	void _Config_Compares(byte modeA, byte modeB, byte modeC);
	void _Config_ClearCtrlRegs() { ClrRegs(); };
	void _Config_InterruptMask(byte ovf, byte oc_A, byte oc_B, byte oc_C);
	void _Config_WGFmode(const byte comp_mode_id);

	void show_regs() const { showOCRegs(); }

	void setOCRegs(uint16_t Aval, uint16_t Bval, uint16_t Cval, uint16_t Dval = 0);

	void showOCRegs() const;

};

extern OneShot16_onT1  myOneShot16_onT1;

