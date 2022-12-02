// T2_setup.h

#ifndef _T2_SETUP_h
#define _T2_SETUP_h

#include "arduino.h"

enum T2_wfgmode { T2_WGM_NORMAL, T2_WGM_CTC };
enum T2_CompOutMode { T2_COM_DISCONNECT = 0, T2_COM_TOGGLE };

enum T2_pscale { T2_PSCALE_0, T2_PSCALE_1, T2_PSCALE_8, T2_PSCALE_32, T2_PSCALE_64, T2_PSCALE_128, T2_PSCALE_256, T2_PSCALE_1024, T2_PSCALE_N };
const int T2_pscale_div[T2_PSCALE_N] = { 0,1,8,32,64,128,256,1024};
#define T2_prescale_factor(a) T2_pscale_div[a]							// 2 tck


void T2_set_wfgmode(T2_wfgmode wfg_mode);

void T2_set_intmask(byte oc_A, byte oc_B, byte ovf);

void T2_set_prescaler(T2_pscale prescale_selector);

void T2_set_comA(T2_CompOutMode co_mode);

void T2_set_comB(T2_CompOutMode co_mode);

unsigned int T2_prescale_factor_old(const T2_pscale prescale_selector);

#endif

