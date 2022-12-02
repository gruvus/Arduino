// wave_gen_math.h

#ifndef _WAVE_GEN_MATH_h
#define _WAVE_GEN_MATH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

//===============================

float fmap(float x, float in_min, float in_max, float out_min, float out_max);

