#pragma once
#if 0
#include "arduino.h"
#include "..\@Utils\utils.h"
#include "T1_setup.h"

#define DEFAULT_DURATION_MS 5.0		// default duration in ms

class TimerOneShot16
{
public:   // public members


	//volatile bool			single_shot;
	volatile unsigned int	call_count;
	volatile voidFuncPtr	event_handler; // this gets called on interrupt event

	// read-only (const references)
	const T1_pscale_id& pscale_id;
	const uint32_t& divisor;
	const float& tpclk;
	const float& duration;
	const volatile uint16_t& counter_bottom;


private:     // private members
	T1_pscale_id			_pscale_id;	// PSCALE_1,8,64,256,1024
	volatile uint16_t		_counter_bottom; // 

	float			_tpclk;
	float			_duration;
	uint16_t		_pscale_factor;
	uint32_t		_div;
	const uint16_t	_counter_top;
	bool			_initialized;

	// ********* methods **********
public:
	TimerOneShot16();

	void Stop() { T1_set_prescaler(T1_PSCALE_0); }		// stop the clock
	void Start() { T1_set_prescaler(pscale_id); };		// run the clock}
	void Reset() { TCNT1 = counter_bottom; };
	void Go() { Start(); };
	void Restart() { Reset();	Start(); };
	void Initialize(const float T = DEFAULT_DURATION_MS);

	void DoNext(const float T, voidFuncPtr action);

	void SetDuration(const float T);


	const void ShowInfo();


private:

	void _ConfigureHardware();

};

namespace globl
{
	extern TimerOneShot16 myOneShotTimer16;
}

#endif