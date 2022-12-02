// T2_set_micros_alt.h

#ifndef _T2_SET_MICROS_ALT_h
#define _T2_SET_MICROS_ALT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//const byte TestPinMode = 0;			// 0: A sets, B clears
////const byte TestPinMode = 1;			// 1: B sets, A clears
//
//
//enum T2_wfgmode { WGM_NORMAL, WGM_CTC };
//enum T2_pscale { PSCALE_1, PSCALE_8, PSCALE_32, PSCALE_64, PSCALE_128, PSCALE_256, PSCALE_1024 };
//enum T2_CompOutMode { COM_DISCONNECT = 0, COM_TOGGLE };
//
//void set_wfgmode(T2_wfgmode wfg_mode);
//
//void set_intmask(byte oc_A, byte oc_B, byte ovf);
//
//void set_prescaler(T2_pscale prescale_factor);
//
//void set_comA(T2_CompOutMode co_mode);
//
//void set_comB(T2_CompOutMode co_mode);
//
//byte prescale_factor(T2_pscale prescale_factor);

#endif

