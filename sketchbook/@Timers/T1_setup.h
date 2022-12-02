// T1_setup.h
#pragma once

/*

#include "arduino.h"


enum T1_wfgmode { T1_WGM_NORMAL, T1_WGM_CTC };
enum T1_CompOutMode { T1_COM_DISCONNECT = 0, T1_COM_TOGGLE };

enum T1_pscale_id { T1_PSCALE_0, T1_PSCALE_1, T1_PSCALE_8, T1_PSCALE_64, T1_PSCALE_256, T1_PSCALE_1024, T1_PSCALE_N };
const int T1_pscale_div[T1_PSCALE_N] = { 0,1,8,64,256,1024 };

#define T1_prescale_factor(a) T1_pscale_div[a]							// 2 tck


void T1_set_wfgmode(T1_wfgmode wfg_mode);

void T1_set_intmask(byte oc_A, byte oc_B, byte ovf);

void T1_set_prescaler(T1_pscale_id prescale_factor);

void T1_stop();

void T1_set_comA(T1_CompOutMode co_mode);

void T1_set_comB(T1_CompOutMode co_mode);



*/