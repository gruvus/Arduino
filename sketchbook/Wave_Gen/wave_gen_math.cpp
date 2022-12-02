// 
// 
// 

#include "wave_gen_math.h"

//===============================
float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
    float slope = (out_max - out_min) / (in_max - in_min);
    float v = (x - in_min) * slope + out_min;
    return v;
}

