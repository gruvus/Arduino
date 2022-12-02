//#define DBG
//#define TRC
//#define HIDE_ISR

/* uses test pins 
TIMING_PIN	in ISR(TIMER1_OVF_vect)
PROBE_PIN	in ISR(TIMER1_COMPA_vect) and SR(TIMER1_COMPB_vect) 
*/

#define TIMING_PIN 12		
#define PROBE_PIN 7 		

#include "..\@Utils\utils_test_pins.h"
#include "Timer_OneShot.h"

#ifdef TRC
#define trace(a) a
#else
#define trace(a)
#endif


//--------------------------------------------------------------
TimerOneShot16::TimerOneShot16()
// must initialize
	: event_handler{ Action_Nothing }
	, _counter_top{ 0xffff }	// UMAX16; // fixed in Normal mode
	, _initialized{false}

	// these are actually intilized in the initial configuration
	, _counter_bottom{ 0 }
	, _pscale_id{ T1_PSCALE_64 } // PSCALE_1,8,64,256,1024

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
void TimerOneShot16::Initialize(const float T)
{
	dpr("<TimerOneShot16::Initialize>"); dtb; dpr(T);
		dnl;

	_ConfigureHardware();  // sets hw timer control registers, interrupts, etc 

	_initialized = true;

	SetDuration(T);		// set default duration, in ms

	// calculated dependent values for reporting
	_pscale_factor = T1_prescale_factor(_pscale_id);


	_div = _counter_top - _counter_bottom + 1L;

	_tpclk = _pscale_factor / (F_CPU / 1000000.0);
	_duration = tpclk * divisor / 1000.0;  //milliseconds

}

//--------------------------------------------------------------
void TimerOneShot16::_ConfigureHardware()
{
	// initialize hw Timer1 in NormalVar mode; generates overflow interrupt at TOP 
	{
		noInterrupts();           // disable all interrupts, clear control registers
		TCCR1A = 0; 	TCCR1B = 0;		TIMSK1 = 0;
		// set interrupts: overflow,  A,B only for test
		T1_set_intmask(1, 1, 1);
		// set Waveform Generation Mode
		T1_set_wfgmode(T1_WGM_NORMAL);
		// set Compare Output Mode
		T1_set_comA(T1_COM_TOGGLE);	// observe OC1A on pin 9
		T1_set_comB(T1_COM_TOGGLE);	// observe OC1B on pin 10
	}

	// for observation, may not need in applictions, should be able to exclude
	{
		// can observe OC1A/B on pins 9/10
		pinMode(9, OUTPUT);		// OC1A
		pinMode(10, OUTPUT);	// OC1B

		SetupTestPins; // uses test pins
		// TIMING_PIN	in ISR(TIMER1_OVF_vect)
		// PROBE_PIN	in ISR(TIMER1_COMPA_vect) and SR(TIMER1_COMPB_vect)
	}

	// get ready
	
	Stop();			// hold the clock, do not start yet
//	Reset();		// TCNT1 = counter_bottom;		// preload counter 
	interrupts();   // enable interrupts

	// ready to go

}

//--------------------------------------------------------------
void TimerOneShot16::SetDuration(const float T) {
	// const float T : target duration/period in miliseconds
	// determines pscale factor and divisor

	trace(dpr("<TimerOneShot16::SetDuration>"); dtb; dpr(T); dtb;)

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
	T1_pscale_id& s = _pscale_id;   s = T1_PSCALE_1; // start with the lowest pre-scale factor available
	while (!done) {
		_pscale_factor = T1_prescale_factor(s);
		//_div = round(T * F_CPU / 1000 / _pscale_factor);
		_div = (T * F_CPU / 1000 / T1_prescale_factor(s));
		if (_div <= 65536)
		{
			done = true; found = true;
		}
		else {
			switch (s) {
			case T1_PSCALE_1:	s = T1_PSCALE_8;	break; // will try next one
			case T1_PSCALE_8:	s = T1_PSCALE_64;	break;
			case T1_PSCALE_64:	s = T1_PSCALE_256;	break;
			case T1_PSCALE_256: s = T1_PSCALE_1024; break;
			case T1_PSCALE_1024: _div = 65536;	done = true; found = false; break; // nothing left to try
			}
		}
	}  // while (!done)
	// at this point _div and _pscale_factor are determined
	//_pscale_id = s;		// update _pscale_id for checking/reporting ; may not be needed in applications
	//_pscale_factor = T1_prescale_factor(s); // already

	_tpclk = _pscale_factor / (F_CPU / 1000000.0); // prescaled clock period, microseconds
	if (found)
		_duration = T; // may not be corect if _div == 65536 (counter_bottom == 0)
	else
		_duration = tpclk * divisor;

	_counter_bottom = 1 + _counter_top - divisor; 

	{
		// set compare values
		OCR1A = _counter_top;		
		OCR1B = _counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
		// ProbeTestPin: B sets, A clears in comp match ISRs
	}

}

//--------------------------------------------------------------
const void TimerOneShot16::ShowInfo() {


	TimerOneShot16& myT = *this;


	dpr("<TimerOneShot16::ShowInfo> ");  
	dpr("Action at ["); dprc((uint32_t)event_handler,HEX);
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
	dpr("\tOCR1A"); dtb; dpr(OCR1A);  dnl;
	dpr("\tOCR1B  "); dtb; dpr(OCR1B); dnl;
	dpr("\twidth  "); dtb; dpr(OCR1A - OCR1B);  dnl;
	dpr("\n");
	dflush;

}

//--------------------------------------------------------------
void TimerOneShot16::DoNext(const float T, voidFuncPtr action) {

	SetDuration(T);

	event_handler = action;

	Restart();

}

//--------------------------------------------------------------
//void TimerOneShot16::Stop()		{ T1_set_prescaler(T1_PSCALE_0);}
//void TimerOneShot16::Start()	{ T1_set_prescaler(pscale_id); } // run the clock}		
//void TimerOneShot16::Reset()	{ TCNT1 = counter_bottom;}
//void TimerOneShot16::Go()		{ Start();}
//void TimerOneShot16::Restart()	{ Reset();	Start();}


TimerOneShot16 globl::myOneShotTimer; // create one global instance  // Serial is not open yet

//--------------------------------------------------------------
#ifndef HIDE_ISR
ISR(TIMER1_OVF_vect) {

	TimerOneShot16& meTmr = globl::myOneShotTimer;		// brevity

	SetTimingPin;

	T1_set_prescaler(T1_PSCALE_0); // stop timer clock

	// meTmr.call_count++;		// if needed

	interrupts();  // to allow millis() to update in lengthy handler

	//if(event_handler)	
	meTmr.event_handler(); // if assigned ...

	//if (!meTmr.single_shot) // may havea "burst" mode?  ... scope creep
	//	TCNT1 = meTmr.counter_bottom;   // reload start value if free run

	ClearTimingPin;
}

ISR(TIMER1_COMPA_vect) {

	ClearProbePin;

}

ISR(TIMER1_COMPB_vect) {

	SetProbePin;

}

#endif
///////////////////////////////////////////////////////

//void TimerOneShot16::_findFactors(const float T)
//{
//	// const float T : target duration/period in miliseconds
//	// determines pscale factor and divisor
//
//	//float t_pclk = T1_prescale_factor(myT.PSCALE) / (F_CPU / 1000000.0); // micros
//	//_div = 1000 * T / t_pclk;
//
//	bool done = false;
//	T1_pscale_id s = T1_PSCALE_1; // start with the lowest pre-scale available
//	while (!done) {
//		_pscale_factor = T1_prescale_factor(s);
//		_div = round(T * F_CPU / 1000 / _pscale_factor);
//		//_div = (T * F_CPU / 1000 / T1_prescale_factor(s));
//		if (_div <= 65536)
//			done = true;
//		else {
//			switch (s) {
//			case T1_PSCALE_1:	s = T1_PSCALE_8;	break; // will try next one
//			case T1_PSCALE_8:	s = T1_PSCALE_64;	break;
//			case T1_PSCALE_64:	s = T1_PSCALE_256;	break;
//			case T1_PSCALE_256: s = T1_PSCALE_1024; break;
//			case T1_PSCALE_1024: _div = 65536;	done = true; break; // nothing left to try
//			}
//		}
//	}  // while (!done)
//
//	_pscale_id = s;
//	// 		_pscale_factor = T1_prescale_factor(s); // already
//
//	_tpclk = _pscale_factor / (F_CPU / 1000000.0); // microseconda
//
//	return;
//
//}
