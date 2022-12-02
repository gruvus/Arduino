// T1_aux.h

#ifndef _T1_aux_h
#define _T1_aux_h

#include "arduino.h"

#include "T1_setup.h"

//#define T1_prescale_factor(a) T1_pscale_div[a]							// 2 tck
unsigned int T1_prescale_factor_old(const T1_pscale_id prescale_factor);		// 2 tck
unsigned int T1_prescale_factor_new(const T1_pscale_id prescale_factor);		// 2 tck


void ShowConfig_T1(char* msg);
void ShowConfig_T1();

void Show16bitRegisters_T1(char* msg);
void Show16bitRegisters_T1();

struct myT1_t {
	T1_pscale_id PSCALE = T1_PSCALE_64;	// PSCALE_1,8,64,256,1024
	uint32_t div = 1;

	volatile uint16_t counter_bottom = 0; // 
	volatile bool single_shot = false;
	volatile unsigned int call_count = 0;
	volatile voidFuncPtr event_handler = Action_Nothing;

	uint16_t counter_top = 0xffff;
	float tpclk;
};

extern myT1_t myT;

void FindFactors(const float T);
void FindFactors_new(const ulong T);

void BestFactors(const float arg_T);

void ShowScaleFactors();



#endif

