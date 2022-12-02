


#include "T_OneShot_Base.h"

//#define DBG
//#define HIDE_ISR

#define trace(a) 


//--------------------------------------------------------------
OneShotBase::OneShotBase(const HwSpec& arg_hwspec)
// must initialize
	: _initialized{ false }
	, event_handler{ Action_Nothing }
	//, _counter_top{ 0xff }	// UMAX8; // fixed in Normal mode

	// these are actually set in the initial configuration
	, _counter_bottom{ 0 }

	, _pscale_id{ 1 } 

	//// const references to internal fields -  must initialize
	, divisor{ _div }
	//, tpclk{ _tpclk }
	, duration{ _duration_t }
	, pscale_id{ _pscale_id }
	, counter_bottom{ _counter_bottom }

	// derived specific
	, hwspec{ arg_hwspec }
	//, _MaxDiv{ arg_hwspec.maxDiv } // hwspec is not initialized yet -> by value would not work
	//, _counter_top{ arg_hwspec.maxCount}
	//, MaxDiv{ hwspec.maxDiv }	// ok as reference, just an alias
	, counter_top{ hwspec.maxCount}

{
	// Initialize(); 
	// could initialize here but Serial would not be avaialable yet 
	// if instance is created at global scope 
}

//--------------------------------------------------------------
void OneShotBase::Initialize(const uint32_t Tus = 5000)

{
	dpr("<OneShotBase::Initialize>"); dtb; dpr(Tus); dpr("us = "); dpr(Tus / 1000.0);
	dnl;
	show_hw_specs();

	SetupTestPins; // uses test pins

	_ConfigureHardware();  // sets hw timer control registers, interrupts, etc 

	_initialized = true;

	SetDuration(Tus);		

};

//--------------------------------------------------------------
void OneShotBase::_ConfigureHardware() {

	// initialize hw Timer1 in NormalVar mode; generates overflow interrupt at TOP 

	noInterrupts();          
	_Config_ClearCtrlRegs();

	// set interrupts: overflow only
	_Config_InterruptMask(1,0,0,0);

	// set Waveform Generation Mode: 0 - Normal
	_Config_WGFmode(0);

	_Config_Compares(0,0,0);  // set Compare Output Mode

	// get ready

	Stop();			// hold the clock, do not start yet
	//	Reset();	// preload counter 

	interrupts();   // enable interrupts

	// ready to go
};


//--------------------------------------------------------------
void OneShotBase::SetDuration(const uint32_t T) {
	// const uint32_t T : target duration/period in microseconts
	// determines pscale factor and divisor
	// >>> uses ps_limits and shifts (div/mult by 2)
	// v5t only integer operations
	//ClearProbePin;

	trace(dpr("<OneShot_Base::SetDuration>"); dtb; dpr(T); dnl);

	if (!_initialized) { Initialize(T); }

	if (T == duration) { return; }		// nothing to do

	// - - - - - - - - - - - - - -

	trace(
		auto watch = [&](byte& s, uint32_t T, uint32_t limit, byte exp2dif) {
			dtb; dpr("<Trace>"); dnl;
			dtb; dtb; dpr("                s ");	dtb;  dpr(s); dnl;
			dtb; dtb; dpr("       _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
			dtb; dtb; dpr("      _pscale_div ");	dtb;  dpr(_pscale_div); dnl;
			dtb; dtb; dpr("             _div ");	dtb;  dpr(_div); dnl;
			dtb; dtb; dpr("                T ");	dtb;  dpr(T); dnl;
			dtb; dtb; dpr("    hwspec.ps_lim ");	dtb;  dpr(limit); dnl;
			dtb; dtb; dpr("hwspec.ps_exp2dif ");	dtb;  dpr(exp2dif); dnl;
		};
	);

	trace(dpr("executing");  dtb; dpr(T);  dtb; dpr(duration / 1000); dnl;);

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available
	//SetProbePin;
	_div = (T * fcpuMHz); // 2.3us multiply by 16 ( = clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )
	//ClearProbePin;

	while (!done) {	// ~0.5us loop overhead
		//ToggleAuxPin;
		//ToggleAuxPin;

		_div = (_div >> hwspec.ps_exp2dif[s]);	// 
		//ToggleAuxPin;

		trace(watch(s, T, hwspec.ps_limits[s], hwspec.ps_exp2dif[s]); dnl;);

		if (_div <= hwspec.maxDiv)
		{
			if (_div < 1) _div = 1;	// only if zero
			done = true; found = true;
		}
		else {
			if (s < hwspec.ps_Nsteps) {
				s++;
			}
			else {
				_div = hwspec.maxDiv;	done = true; found = false;
			}
		}
		//ToggleAuxPin;

	}  // while (!done)
	//SetProbePin;

	_counter_bottom = 1 + counter_top - divisor;

	// at this point _div and _pscale_div are determined

	_pscale_div = hwspec.ps_divs[s];	// <1.2us
	_tpclk = _pscale_div / float(fcpuMHz); // prescaled clock period, microseconds

	_duration_t = T ; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	_duration_a = tpclk() * divisor;

	trace(
		{
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
			dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
			dtb; dpr("   _pscale_div ");	dtb;  dpr(_pscale_div); dnl;
			dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
			dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
			dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
			dtb; dpr("         tpclk ");	dtb;  dpr(tpclk()); dnl;

			dtb; dpr("             T ");	dtb;  dpr(T); dnl;
			dtb; dpr("   _duration_t ");	dtb;  dpr(_duration_t); dnl;
			dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
			dnl; dflush;
		}
	)
}


//--------------------------------------------------------------
void OneShotBase::show_config() const {


	dpr("<OneShotBase::show_config> ");
	dpr("Will call function at ["); dprc((uint32_t)event_handler, HEX);
	dpr("] after "); dpr(_duration_a); dpr("us = "); dpr(_duration_a /1000.0); dpr("ms"); dnl;
	dnl;
	dtb; dpr("_duration_t "); dtb; dpr(_duration_t); dtb; dpr(duration);  dnl;
	dtb; dpr("_duration_a "); dtb; dpr(_duration_a); dtb; dpr(duration);  dnl;
	dtb; dpr("_pscale_id  "); dtb; dpr(_pscale_id); dtb; dpr(pscale_id);  dnl;
	dtb; dpr("_pscale_num "); dtb; dpr(_pscale_div); dtb; dpr("");  dnl;
	dtb; dpr("_tpclk      "); dtb; dpr(_tpclk); dtb; dpr(tpclk());  dnl;
	dnl;
	dtb; dpr(" counter_top    "); dtb; dpr("   ");  dtb; dpr(counter_top); dnl;
	dtb; dpr("_counter_bottom "); dtb; dpr(_counter_bottom); dtb; dpr(counter_bottom);  dnl;
	dtb; dpr("_div            "); dtb; dpr(_div); dtb; dpr(divisor);  dnl;

	dnl;
	show_regs();

	//dnl;
	//show_hw_specs();
	dnl;
	dflush;

}

void OneShotBase::show_hw_specs() const {
	dtb; dpr("hwspec.bits      "); dtb; dpr(hwspec.bits); dnl;

	dtb; dpr("hwspec.ps_divs   "); dtb;
	byte N = hwspec.ps_Nsteps + 1;
	for (byte i = 0; i < N; i++) {
		dpr(hwspec.ps_divs[i]); dpr(", ");
	}dnl;
	dtb; dpr("hwspec.ps_Nsteps "); dtb; dpr(hwspec.ps_Nsteps); dnl;
	dtb; dpr("hwspec.ps_limits "); dtb;
	for (byte i = 0; i < N; i++) {
		dpr(hwspec.ps_limits[i]); dpr(", ");
	}dnl;
	dtb; dpr("hwspec.ps_exp2dif "); dtb;
	for (byte i = 0; i < N; i++) {
		dpr(hwspec.ps_exp2dif[i]); dpr(", ");
	}dnl;
	dtb; dpr("hwspec.maxCount  "); dtb; dpr(hwspec.maxCount); dnl;
	//dtb; dpr("_counter_top       "); dtb; dpr(counter_top); dnl;
	dtb; dpr("hwspec.maxDiv    "); dtb; dpr(hwspec.maxDiv); dnl;
	//dtb; dpr("_MaxDiv            "); dtb; dpr(MaxDiv); dnl;

	dflush;
};
