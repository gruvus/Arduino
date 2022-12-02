#include "Timer_OneShot.h"


#if 0
namespace {
	void SetDuration_ms(const float Tms);

	void SetDuration_ms_v4(const float Tms);

	void SetDuration_v4t(const float Tms);

	void SetDuration_v3(const float Tms);

	void SetDuration_v2(const float Tms);

	void SetDuration_v1(const float Tms);

	uint16_t _PrescaleFactor(byte pscale_id)
	{
		if (pscale_id > hwspec.ps_Nsteps) {
			dpr("<_PrescaleFactor> Invalid pscale_id "); dpr(pscale_id); dnl;
			return hwspec.ps_divs[hwspec.ps_Nsteps];
		}
		return hwspec.ps_divs[pscale_id];
	};
	void Initialize_ms(const float Tms);
}
#endif

#if 0

//--------------------------------------------------------------
void OneShotBase::SetDuration_us_v5t(const uint32_t T = 5000) {
	// const uint32_t T : target duration/period in microseconts
	// determines pscale factor and divisor
	// >>> uses ps_limits and shifts (div/mult by 2)
	// v5t only integer operations
	ClearProbePin;

	if (!_initialized) { Initialize_us(T); }

	//if (Tus == duration) { return; }		// nothing to do

	//uint32_t T = Tms * 1000;	//T in microseconds

	// - - - - - - - - - - - - - -

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available
	SetProbePin;
	_div = (T * fcpuMHz); // 2.3us multiply by 16 ( = clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )
	ClearProbePin;

	while (!done) {	// ~0.5us loop overhead
		ToggleAuxPin;
		ToggleAuxPin;

		_div = (_div >> hwspec.ps_exp2dif[s]);	//
		ToggleAuxPin;

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
		ToggleAuxPin;

	}  // while (!done)
	SetProbePin;

	_counter_bottom = 1 + counter_top - divisor;

	// at this point _div and _pscale_div are determined

	_pscale_div = hwspec.ps_divs[s];	// <1.2us
	_tpclk = _pscale_div / float(fcpuMHz); // prescaled clock period, microseconds

	if (found)
		_duration_t = T; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

void OneShotBase::Initialize_ms(const float Tms)

{
	dpr("<OneShotBase::Initialize (ms)>"); dtb; dpr(Tms); dtb; dpr(Tms * 1000);
	dnl;
	show_hw_specs();
	SetupTestPins; // uses test pins
	// TIMING_PIN	in ISR(TIMER1_OVF_vect)
	// PROBE_PIN	in ISR(TIMER1_COMPA_vect) and SR(TIMER1_COMPB_vect)

	dnl;

	_ConfigureHardware();  // sets hw timer control registers, interrupts, etc 

	_initialized = true;

	SetDuration_ms(Tms);

};

void OneShotBase::SetDuration_ms(const float Tms = 5) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor
	// >>> uses ps_limits and shifts (div/mult by 2)
	// v4 only integer operations

	if (!_initialized) { Initialize_ms(Tms); }

	if (Tms == duration) { return; }		// nothing to do

	uint32_t T = Tms * 1000;	//T in microseconds

	// - - - - - - - - - - - - - -

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available

	_div = (T * fcpuMHz); // 2.3us multiply by 16 ( = clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )

	while (!done) {	// ~0.5us loop overhead

		_div = (_div >> hwspec.ps_exp2dif[s]);	// 

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

	}  // while (!done)

	_counter_bottom = 1 + counter_top - divisor;

	// at this point _div and _pscale_div are determined

	_pscale_div = hwspec.ps_divs[s];	// <1.2us
	_tpclk = _pscale_div / float(fcpuMHz); // prescaled clock period, microseconds

	if (found)
		_duration_t = Tms; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

void OneShotBase::SetDuration_v4t(const float Tms = 5) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor
	// >>> uses ps_limits and shifts (div/mult by 2)
	// only integer operations


	auto watch = [&](byte& s, uint32_t T, uint32_t limit, byte exp2) {
		dtb; dpr("<Trace>"); dnl;
		dtb; dtb; dpr("              s ");	dtb;  dpr(s); dnl;
		dtb; dtb; dpr("     _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dtb; dpr(" _pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dtb; dpr("           _div ");	dtb;  dpr(_div); dnl;
		dtb; dtb; dpr("              T ");	dtb;  dpr(T); dnl;
		dtb; dtb; dpr(" hwspec.ps_lim ");	dtb;  dpr(limit); dnl;
		dtb; dtb; dpr("hwspec.ps_exp2 ");	dtb;  dpr(exp2); dnl;

		//dtb; dpr("        MaxDiv ");	dtb;  dpr(MaxDiv); dnl;
	};

	ClearProbePin;

	trace(dpr("<OneShot8::SetDuration>"); dtb; dpr(Tms); dtb;);

	if (!_initialized) {
		trace(dpr("not intialized"); dnl;);
		Initialize_ms(Tms);
	}

	if (Tms == duration) {
		trace(dpr("nothing to do"); dnl; dnl;);
		return;	// nothing to do
	}

	uint32_t T = Tms * 1000;	//T in microseconds

	trace(dpr("executing");  dtb; dpr(T);  dtb; dpr(Tms);  dtb; dpr(duration * 1000); dnl;);
	// - - - - - - - - - - - - - -

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available

	SetProbePin;
	_div = (T * fcpuMHz); // 2.3us multiply by 16 ( = clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )
	ClearProbePin;

	while (!done) {	// ~0.5us loop overhead

		ToggleAuxPin;
		ToggleAuxPin;
		_div = (_div >> hwspec.ps_exp2dif[s]);	// 	1.7us (0)/ 3.0us (3) / 2.5us (2)
		//_div = _div /hwspec.ps_multiplier[s];	// 	38us ! - slower  (4.4us to multiply)

		ToggleAuxPin;

		trace(watch(s, T, hwspec.ps_limits[s], hwspec.ps_exp2[s]); dnl;);

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


		ToggleAuxPin;

	}  // while (!done)

	SetProbePin;

	_counter_bottom = 1 + counter_top - divisor;

	// at this point _div and _pscale_div are determined

		//_pscale_div = _PrescaleFactor(s);	// 1.4us
	_pscale_div = hwspec.ps_divs[s];	// <1.2us
	_tpclk = _pscale_div / float(fcpuMHz); // prescaled clock period, microseconds

	if (found)
		_duration_t = Tms; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

void OneShotBase::SetDuration_v3(const float Tms = 5) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor
	// >>> uses ps_limits and shifts (div/mult by 2)
	// only integer operations


	auto watch = [&](byte& s, uint32_t T, uint32_t limit, byte exp2) {
		dtb; dpr("<Trace>"); dnl;
		dtb; dtb; dpr("              s ");	dtb;  dpr(s); dnl;
		dtb; dtb; dpr("     _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dtb; dpr(" _pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dtb; dpr("           _div ");	dtb;  dpr(_div); dnl;
		dtb; dtb; dpr("              T ");	dtb;  dpr(T); dnl;
		dtb; dtb; dpr(" hwspec.ps_lim ");	dtb;  dpr(limit); dnl;
		dtb; dtb; dpr("hwspec.ps_exp2 ");	dtb;  dpr(exp2); dnl;

		//dtb; dpr("        MaxDiv ");	dtb;  dpr(MaxDiv); dnl;
	};

	ClearProbePin;

	trace(dpr("<OneShot8::SetDuration>"); dtb; dpr(Tms); dtb;)

		if (!_initialized) {
			trace(dpr("not intialized"); dnl;);
			Initialize_ms(Tms);
		}


	if (Tms == duration) {
		trace(dpr("nothing to do"); dnl; dnl;);
		return;	// nothing to do
	}

	uint32_t T = Tms * 1000;	//T in microseconds

	trace(dpr("executing");  dtb; dpr(T);  dtb; dpr(Tms);  dtb; dpr(duration * 1000); dnl;);
	// - - - - - - - - - - - - - -

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available
	_div = T;
	SetProbePin;
	//trace(watch(s, ddiv); dnl;)
	_div = (_div << 4); //  2.3us multiply by 16 ( = CPU clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )
	//_div = (_div * fcpuMHz); // 2.3us multiply by 16 ( = clock ticks/microsecond - there's a hw define in general but relying on 16(MHz) = 2^4  )

	ClearProbePin;

	while (!done) {	// ~0.5us loop overhead

		ToggleAuxPin;
		//_pscale_div = _PrescaleFactor(s);	// 1.4us
		//_pscale_div = hwspec.ps_divs[s];	// <1.2us
		ToggleAuxPin;
		//_div = (_div >> (hwspec.ps_exp2[s] - hwspec.ps_exp2[s-1]));	// 2.5 us .ps_exp2[0] =0 (must !!)
		_div = (_div >> hwspec.ps_exp2dif[s]);	// 	1.7us (0)/ 3.0us (3) / 2.5us (2)

		ToggleAuxPin;

		trace(watch(s, T, hwspec.ps_limits[s], hwspec.ps_exp2[s]); dnl;);

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


		ToggleAuxPin;

	}  // while (!done)

	SetProbePin;

	// at this point _div and _pscale_div are determined

		//_pscale_div = _PrescaleFactor(s);	// 1.4us
	_pscale_div = hwspec.ps_divs[s];	// <1.2us

	_tpclk = _pscale_div / (F_CPU / 1000000.0); // prescaled clock period, microseconds

	if (found)
		_duration_t = Tms; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	_counter_bottom = 1 + counter_top - divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

void OneShotBase::SetDuration_v2(const float Tms = 5) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor

	// >>> uses ps_limits; one float calculation at end

	auto watch = [&](byte& s, uint32_t& T, uint32_t limit) {
		dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("hwspec.ps_lim ");	dtb;  dpr(limit); dnl;

		//dtb; dpr("        MaxDiv ");	dtb;  dpr(MaxDiv); dnl;
	};


	trace(dpr("<OneShot8::SetDuration>"); dtb; dpr(Tms); dtb;)

		if (!_initialized) {
			trace(dpr("not intialized"); dnl;);
			Initialize_ms(Tms);
		}
	if (Tms == duration) {
		trace(dpr("nothing to do"); dnl; dnl;);
		return;	// nothing to do
	}
	trace(dpr("executing");  dtb; dpr(Tms * 1000);  dtb; dpr(duration * 1000); dnl;);
	// - - - - - - - - - - - - - -
	ClearProbePin;

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available
	uint32_t T = Tms * 1000;	//T in microseconds
	//trace(watch(s, ddiv); dnl;)

	while (!done) {
		ToggleAuxPin;
		_pscale_div = _PrescaleFactor(s);
		ToggleAuxPin;

		//_div = round(T * F_CPU / 1000 / _pscale_div);
		//_div = (T * F_CPU / 1000 / _pscale_div);
		ToggleAuxPin;

		trace(watch(s, T, hwspec.ps_limits[s]); dnl;);


		if (T <= hwspec.ps_limits[s])
		{
			if (T < 1)		// how to handle zero?
				_div = 1;
			else {
				_div = (T / _pscale_div) * (F_CPU / 1000000);

				done = true; found = true;
			}
		}
		else {
			if (s < hwspec.ps_Nsteps) {
				s++;
			}
			else {
				_div = MaxDiv;	done = true; found = false;
			}
		}


		ToggleAuxPin;

	}  // while (!done)

	SetProbePin;

	// at this point _div and _pscale_div are determined

	_tpclk = _pscale_div / (F_CPU / 1000000.0); // prescaled clock period, microseconds
	if (found)
		_duration_t = Tms; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	_counter_bottom = 1 + counter_top - divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

void OneShotBase::SetDuration_v1(const float T = 5) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor
	// one float calculations each iteration

	auto watch = [&](byte& s, const double& ddiv) {
		dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("          ddiv ");	dtb;  dpr(ddiv); dnl;
		//dtb; dpr("        MaxDiv ");	dtb;  dpr(MaxDiv); dnl;
	};


	trace(dpr("<OneShot8::SetDuration>"); dtb; dpr(T); dtb;)

		if (!_initialized) {
			trace(dpr("not intialized"); dnl;);
			Initialize_ms(T);
		}
	if (T == duration) {
		trace(dpr("nothing to do"); dnl; dnl;);
		return;	// nothing to do
	}
	trace(dpr("executing");  dtb; dpr(T * 1000);  dtb; dpr(duration * 1000); dnl;);

	ClearProbePin;

	bool done = false, found = false;
	byte& s = _pscale_id;   s = 1; // start with the lowest pre-scale factor available

	//trace(watch(s, ddiv); dnl;)

	while (!done) {
		ToggleAuxPin;
		_pscale_div = _PrescaleFactor(s);
		ToggleAuxPin;

		//_div = round(T * F_CPU / 1000 / _pscale_div);

		double ddiv;
		//uint32_t& ddiv = _div;
		ddiv = (T * F_CPU / 1000 / _pscale_div);
		ToggleAuxPin;

		_div = ddiv;

		trace(watch(s, double(ddiv)); dnl;);

		ToggleAuxPin;

		if (ddiv <= MaxDiv)
		{
			if (ddiv < 1) ddiv = 1;
			done = true; found = true;
		}
		else {
			if (s < hwspec.ps_Nsteps) {
				s++;
			}
			else {
				ddiv = MaxDiv;	done = true; found = false;
			}
		}
		ToggleAuxPin;

		_div = ddiv;

		ToggleAuxPin;

	}  // while (!done)

	SetProbePin;

	// at this point _div and _pscale_div are determined

	_tpclk = _pscale_div / (F_CPU / 1000000.0); // prescaled clock period, microseconds
	if (found)
		_duration_t = T; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration_t = tpclk * divisor;

	_counter_bottom = 1 + counter_top - divisor;

	{
		trace(
			dtb; dpr("             s ");	dtb;  dpr(s); dnl;
		dtb; dpr("    _pscale_id ");	dtb;  dpr(_pscale_id); dnl;
		dtb; dpr("_pscale_div ");	dtb;  dpr(_pscale_div); dnl;
		dtb; dpr("          _div ");	dtb;  dpr(_div); dnl;
		dtb; dpr("       divisor ");	dtb;  dpr(divisor); dnl;
		dtb; dpr("        _tpclk ");	dtb;  dpr(_tpclk); dnl;
		dtb; dpr("         tpclk ");	dtb;  dpr(tpclk); dnl;

		dtb; dpr("             T ");	dtb;  dpr(T); dnl;
		dtb; dpr("     _duration_t ");	dtb;  dpr(_duration_t); dnl;
		dtb; dpr("      duration ");	dtb;  dpr(duration); dnl;
		dnl;)
	}
	{
		// set compare values
		OCR2A = counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

#endif