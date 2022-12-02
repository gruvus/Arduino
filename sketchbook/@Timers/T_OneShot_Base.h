// T_OneShot_Base.h
#pragma once

#include "arduino.h"

#define TIMING_PIN 12		
#define PROBE_PIN 7 		
#define AUX_PIN 6 		

#include "..\@Utils\utils_test_pins.h"

#include "..\@Utils\utils.h"

#include "hw_specs.h"



class OneShotBase
{
protected:
	OneShotBase(const HwSpec& hwspec);

	const HwSpec& hwspec;

public:

	volatile voidFuncPtr event_handler;		// this gets called on interrupt event
	
	// read-only (const references)
	const uint32_t& divisor;
	//const float& tpclk;
	const uint32_t& duration;

	const volatile uint16_t& counter_bottom;

	const byte& pscale_id;

private:

	uint32_t		_div;
	float			_tpclk;
	uint32_t		_duration_t;		// target duration
	uint32_t		_duration_a;		// actual duration
	uint16_t		_pscale_div;
	bool			_initialized;

	volatile uint16_t		_counter_bottom; // 


	//const uint32_t& MaxDiv;
	const uint16_t& counter_top; // derived specific

	byte	_pscale_id;	// 


	// ********* methods **********
public:

	virtual void Stop() = 0;		// stop the clock
	virtual void Run() = 0;		// run the clock}
	virtual void Reset() = 0;
	void Restart() { Reset();	Run(); };

	void Initialize(const uint32_t Tus);

	void Initialize(const uint32_t Tus, voidFuncPtr action) {
		Initialize(Tus);
		event_handler = action;
	};

	void SetDuration(const uint32_t Tus);

	void DoLater(voidFuncPtr action, uint32_t T) {
		//ToggleAuxPin;
		SetDuration(T);
		DoLater(action);
		//ToggleAuxPin;
	};

	void DoLater(voidFuncPtr action) {
		event_handler = action;
		Restart();
	};

	float tpclk() const { return _pscale_div / float(fcpuMHz); };

	void show_config() const;
	void show_hw_specs() const;
	virtual void show_regs() const = 0;

	void ActionCall() {
		SetTimingPin;
		Stop();
		//interrupts();  // to allow millis() to update during a lengthy handler
		event_handler(); // always valid
		ClearTimingPin;
	};

private:

	void _ConfigureHardware();

	virtual void _Config_Compares(byte modeA, byte modeB, byte modeC) = 0;
	virtual void _Config_ClearCtrlRegs() = 0;
	virtual void _Config_InterruptMask(byte ovf , byte oc_A, byte oc_B, byte oc_C) = 0;
	virtual void _Config_WGFmode(const byte comp_mode_id) = 0;


public:

	void SetDuration_us_v5t(const uint32_t T);

};


