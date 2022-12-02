
#if 0

//#define DBG
#define TRC
#define HIDE_ISR
#undef TRC

/* uses test pins
TIMING_PIN	in ISR(TIMER2_OVF_vect)
PROBE_PIN	in ISR(TIMER2_COMPA_vect) and SR(TIMER2_COMPB_vect)
*/

#define TIMING_PIN 12		
#define PROBE_PIN 7 		

#include "..\@Utils\utils_test_pins.h"
#include "Timer_OneShot_T2.h"


#ifdef TRC
#define trace(a) a
#else
#define trace(a)
#endif


//--------------------------------------------------------------
TimerOneShot8::TimerOneShot8()
// must initialize
	: event_handler{ Action_Nothing }
	, _counter_top{ 0xff }	// UMAX8; // fixed in Normal mode
	, _initialized{ false }

	// these are actually intilized in the initial configuration
	, _counter_bottom{ 0 }
	, _pscale_id{ T2_PSCALE_64 } // PSCALE_1,8,32,64,128,256,1024

	// const references to internal fileds -  must initialize
	, divisor{ _div }
	, tpclk{ _tpclk }
	, duration{ _duration }
	, pscale_id{ _pscale_id }
	, counter_bottom{ _counter_bottom }
{
	// could be initialized here but Serial would not be avaialable yet if instance is created at global scope 

}

//--------------------------------------------------------------
void TimerOneShot8::Initialize(const float T)
{
	dpr("<TimerOneShot8::Initialize>"); dtb; dpr(T);
	dnl;

	_ConfigureHardware();  // sets hw timer control registers, interrupts, etc 

	_initialized = true;

	SetDuration(T);		// set default duration, in ms

	// calculated dependent values for reporting
	_pscale_factor = T2_prescale_factor(_pscale_id);


	_div = _counter_top - _counter_bottom + 1L;

	_tpclk = _pscale_factor / (F_CPU / 1000000.0);
	_duration = tpclk * divisor / 1000.0;  //milliseconds

}

//--------------------------------------------------------------
void TimerOneShot8::_ConfigureHardware()
{
	// initialize hw Timer1 in NormalVar mode; generates overflow interrupt at TOP 
	{
		noInterrupts();           // disable all interrupts, clear control registers
		TCCR2A = 0; 	TCCR2B = 0;		TIMSK2 = 0;
		// set interrupts: overflow,  A,B only for test
		T2_set_intmask(1, 1, 1);
		// set Waveform Generation Mode
		T2_set_wfgmode(T2_WGM_NORMAL);
		// set Compare Output Mode
		T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
		T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3
	}

	// for observation, may not need in applictions, should be able to exclude
	{
		// can observe OC2A/B on pins 11/3
		pinMode(11, OUTPUT);		// OC1A
		pinMode(3, OUTPUT);			// OC1B

		SetupTestPins; // uses test pins
		// TIMING_PIN	in ISR(TIMER2_OVF_vect)
		// PROBE_PIN	in ISR(TIMER2_COMPA_vect) and ISR(TIMER2_COMPB_vect)
	}

	// get ready

	Stop();			// hold the clock, do not start yet
	//	Reset();		// TCNT2 = counter_bottom;		// preload counter 
	interrupts();   // enable interrupts

	// ready to go

}

//--------------------------------------------------------------
void TimerOneShot8::SetDuration(const float T) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor

	trace(dpr("<TimerOneShot8::SetDuration>"); dtb; dpr(T); dtb;)

		if (!_initialized) {
			trace(dpr("not intialized"); dnl;)
				Initialize(T);
		}
	if (T == duration) {
		trace(dpr("nothing to do"); dnl;)
			return;	// nothing to do
	}
	trace(dpr("executing"); dnl;)

		// Step: _findFactors(T);	// ~90us
		bool done = false, found = false;
	T2_pscale& s = _pscale_id;   s = T2_PSCALE_1; // start with the lowest pre-scale factor available
	while (!done) {
		_pscale_factor = T2_prescale_factor(s);
		//_div = round(T * F_CPU / 1000 / _pscale_factor);
		_div = (T * F_CPU / 1000 / _pscale_factor);
		if (_div <= _MaxDiv)
		{
			if (_div < 1) _div = 1;
			done = true; found = true;
		}
		else {
			switch (s) {
			case T2_PSCALE_1:	s = T2_PSCALE_8;	break; // will try next one
			case T2_PSCALE_8:	s = T2_PSCALE_32;	break;
			case T2_PSCALE_32:	s = T2_PSCALE_64;	break;
			case T2_PSCALE_64:	s = T2_PSCALE_128;	break;
			case T2_PSCALE_128:	s = T2_PSCALE_256;	break;
			case T2_PSCALE_256: s = T2_PSCALE_1024; break;
			case T2_PSCALE_1024: _div = _MaxDiv;	done = true; found = false; break; // nothing left to try
			}
		}
	}  // while (!done)
	// at this point _div and _pscale_factor are determined
	//_pscale_id = s;		// update _pscale_id for checking/reporting ; may not be needed in applications
	//_pscale_factor = T1_prescale_factor(s); // already

	_tpclk = _pscale_factor / (F_CPU / 1000000.0); // prescaled clock period, microseconds
	if (found)
		_duration = T; // may not be corect if _div == _MaxDiv (counter_bottom == 0)
	else
		_duration = tpclk * divisor;

	_counter_bottom = 1 + _counter_top - divisor;

	{
		// set compare values
		OCR2A = _counter_top;
		OCR2B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

//--------------------------------------------------------------
const void TimerOneShot8::ShowInfo() {


	TimerOneShot8& myT = *this;


	dpr("<TimerOneShot8::ShowInfo> ");
	dpr("Action at ["); dprc((uint32_t)event_handler, HEX);
	dpr("] will execute after "); dpr(duration); dpr("ms\n");
	dnl;
	dpr("\tp-scale id  "); dtb; dpr(_pscale_id); dtb; dpr(pscale_id);  dnl;
	dpr("\tp-scale fact"); dtb; dpr(_pscale_factor); dtb; dpr("");  dnl;
	dpr("\tp-clock\t"); dtb; dpr(_tpclk); dtb; dpr(tpclk);  dnl;
	dnl;
	dpr("\tbottom      "); dtb; dpr(_counter_bottom); dtb; dpr(counter_bottom);  dnl;
	dpr("\ttop         "); dtb; dpr(_counter_top); dtb; dpr("");  dnl;
	dpr("\tdivisor     "); dtb; dpr(_div); dtb; dpr(divisor);  dnl;
	dpr("\tduration     "); dtb; dpr(_duration); dtb; dpr(duration);  dnl;

	dnl;
	dpr("\tOCR2A"); dtb; dpr(OCR2A);  dnl;
	dpr("\tOCR2B  "); dtb; dpr(OCR2B); dnl;
	dpr("\twidth  "); dtb; dpr(OCR2A - OCR2B);  dnl;
	dpr("\n");
	dflush;

}

//--------------------------------------------------------------
void TimerOneShot8::DoNext(const float T, voidFuncPtr action) {

	SetDuration(T);

	event_handler = action;

	Restart();

}


TimerOneShot8 globl::myOneShotTimer8; // create one global instance  // Serial is not open yet

//--------------------------------------------------------------
#ifndef HIDE_ISR
ISR(TIMER2_OVF_vect) {

	TimerOneShot8& meTmr = globl::myOneShotTimer8;		// brevity

	SetTimingPin;

	//T2_set_prescaler(T2_PSCALE_0); // stop timer clock
	meTmr.Stop();
	// meTmr.call_count++;		// if needed

	//interrupts();  // to allow millis() to update in lengthy handler

	//if(event_handler)	
	meTmr.event_handler(); // if assigned ...

	//if (!meTmr.single_shot) // may havea "burst" mode?  ... scope creep
	//	TCNT1 = meTmr.counter_bottom;   // reload start value if free run

	ClearTimingPin;
}

ISR(TIMER2_COMPA_vect) {

	ClearProbePin;

}

ISR(TIMER2_COMPB_vect) {

	SetProbePin;

}

#endif
///////////////////////////////////////////////////////

#endif