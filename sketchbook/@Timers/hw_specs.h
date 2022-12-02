// hw_specs.h
#pragma once
#include "arduino.h"

const byte fcpuMHz = 16;

struct HwSpec {
	byte bits;
	int ps_divs[8];	// e.g for T1: { 0,1,8,32,64,128,256,1024 };// always starts with 0
	byte ps_Nsteps; // how many prescaler steps are available (size of ps_divs[] - 1)

	// precalculated values
	uint32_t ps_limits[8];
	//byte ps_exp2[8];
	byte ps_exp2dif[8];
	uint16_t maxCount;
	uint32_t maxDiv;
};


constexpr HwSpec hwspec16
{ 16						//  byte bits;
, {0,1,8,64,256,1024}		//  int ps_divs[8];
, 5							//	byte ps_Nsteps;
, {0, 1 * 4096ul, 8 * 4096ul, 64 * 4096ul, 256 * 4096ul, 1024 * 4096ul} // uint32_t ps_limits[8]
//, {0, 4096, 32768, 262144, 1048576, 4194304}
//, {0,0,3,6,8,10} // 	byte ps_exp2;
, {0,0,3,3,2,2} // 	byte ps_exp2dif;	
//, {0,1,3,8,4,4} // 	byte ps_multiplier[8];
, 65535						//  uint16_t maxCount;
, 65536						//  uint32_t maxDiv;
};


const HwSpec hwspec8
{ 8				//  byte bits;
, {0,1,8,32,64,128,256,1024}		//  int ps_divs[8];
, 7				//	byte ps_Nsteps;
, {0, 1 * 16, 8 * 16, 32 * 16, 64 * 16, 128 * 16, 256 * 16, 1024 * 16}  // uint32_t ps_limits[8]
, {0,0,3,2,1,1,1,2} // 	byte ps_exp2dif;
, 255			//  uint16_t maxCount;
, 256			//  uint32_t maxDiv;
};

/*  C++20 systax below: much nicer but does not build (only sypports C++17)
const HwSpec hwspec8
{ .bits {8}				//  byte bits;
, .ps_divs {0,1,8,32,64,128,256,1024}		//  int ps_divs[8];
, .ps_Nsteps {7}				//	byte ps_Nsteps;
, .maxCount {255}			//  uint16_t maxCount;
, .maxDiv {256}			//  uint32_t maxDiv;
};
*/
