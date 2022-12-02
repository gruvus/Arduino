// T1_aux.h

#if 0

#ifndef _T1_aux_h
#define _T1_aux_h

#include "arduino.h"

#include "T1_setup.h"

enum T1_wfgmode { T1_WGM_NORMAL, T1_WGM_CTC };
enum T1_CompOutMode { T1_COM_DISCONNECT = 0, T1_COM_TOGGLE };

enum T1_pscale_id { T1_PSCALE_0, T1_PSCALE_1, T1_PSCALE_8, T1_PSCALE_64, T1_PSCALE_256, T1_PSCALE_1024, T1_PSCALE_N };
const int T1_pscale_div[T1_PSCALE_N] = { 0,1,8,64,256,1024 };

#define T1_prescale_factor(a) T1_pscale_div[a]							// 2 tck



void ShowConfig_T1(char* msg);
void ShowConfig_T1();

void Show16bitRegisters_T1(char* msg);
void Show16bitRegisters_T1();


void ShowScaleFactors();



#endif

#endif

