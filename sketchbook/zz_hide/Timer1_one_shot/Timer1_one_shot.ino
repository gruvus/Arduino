
#define DBG
#undef DBG

#define ACTIVITY_PIN 13		// on-off action target		// green
#define TIMING_PIN 12		// time in ovfl ISR			// red
#define SYNC_PIN 8			// on-off cycle				// blue
#define PROBE_PIN 7 		// comp A/B set/clear
#define AUX_PIN 6 			// 

#include "utils_test_pins.h"
//#include "utils.h"
#include "T1_setup.h"
#include "T1_aux.h"


//const float tscale		= 2000;		// time scale | 5000 | 1 for osc-scope // high jitter below 0.5
const float tscale		= 1;		// time scale | 5000 | 1 for osc-scope // high jitter below 0.5

const float main_cycle	= 1;		// period of main repeat cycle in ms
const float md1			= 0.5;		// simple action delay
const float md2			= 0.3;		// wiggle action delay
const float wigT		= 0.4;		// total wiggle time in ms
const byte N			= 2;		// number of wiggle cycles

const float min_pause	= 0.1;		//  minimum pause after action

//..... pre calculations

const float pause = main_cycle - max(md1, md2 + wigT);


const long main_dly = (max(md1, md2 + wigT) + pause) * tscale * 1000;

const byte M = 2 * N; 		// total number of wiggle steps (2 per cycle)
// duration of wiggle step in us
const ulong wigStepTime = (wigT * 1000 * tscale) / M; // micros
// float t = (T * tscale) / (2 * N); // milliseconds	// 45us if float
const ulong wigTotalTime = wigT * 1000 * tscale;


myT1_t myT;		// Timer1 wrapper (should be a class)
byte do_print = 2;
//------------------------------------------------------------------------------
void SetupMonoTimer() {
	// initialize timer1 in NormalVar mode; generates overflow interrupt at TOP 
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
	// set initial counting cycle
	myT.counter_top = UMAX16; // fixed in Normal mode
	myT.counter_bottom = 0;		// load start value on overflow (at top)
	{
		Serial.print("  Initial values:\n\n");
		Serial.print("\tBottom\tTop\tSteps\n\t");
		Serial.print(myT.counter_bottom);	Serial.print("\t");
		Serial.print(myT.counter_top);	Serial.print("\t");
		Serial.print(myT.counter_top - myT.counter_bottom + 1L);	Serial.print("\n");
		Serial.flush();
	}

	// set compare values
	OCR1A = myT.counter_top;
	OCR1B = myT.counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled

	{
		Serial.print("\n\tA\tB\tWidth");
		Serial.print("\n\t");
		Serial.print(OCR1B);	Serial.print("\t");
		Serial.print(OCR1A);	Serial.print("\t");
		Serial.print(OCR1A - OCR1B);	Serial.print("\n\n");
		Serial.flush();
	}

	// get ready
	myT.single_shot = true;
	TCNT1 = myT.counter_bottom;		// preload counter 
	T1_stop();						// do not start yet
	interrupts();             // enable all interrupts

	// can observe OC1A/B on pins 9/10
	pinMode(9, OUTPUT);		// OC1A
	pinMode(10, OUTPUT);	// OC1B
}


//------------------------------------------------------------------------------
void setup()
{
	Serial.begin(115200);	Serial.print("\n");

	StartupMessage();
	dpr("Debug printing enabled"); dnl;
	
	SetupTestPins;

	//show parameters
	{
		auto bval = [](bool b) {if (b) return "true";else return "false"; };

		dnl;
		dpr("  Parameters: "); dnl;
		dnl;
		dpr("           tscale = ");  dpr(tscale); dnl;
		dpr("       main_cycle = ");  dpr(main_cycle); dnl;
		dpr("              md1 = ");  dpr(md1); dnl;
		dpr("              md2 = ");  dpr(md2); dnl;
		dpr("             wigT = ");  dpr(wigT); dtb; dpr("N = ");  dpr(N); dnl;
		dpr("        min_pause = ");  dpr(min_pause); dnl;
		dnl;
		dpr("            pause = ");  dpr(pause); dtb; dpr("pause > min_pause = "); dpr(logic(pause > min_pause)); dnl;
		dpr("         main_dly = ");  dpr(main_dly); dnl; 
		dnl;
		dpr("     wigTotalTime = ");  dpr(wigTotalTime); dnl;
		dpr("      wigStepTime = ");  dpr(wigStepTime); dtb; dpr("M = ");  dpr(M); dnl;
		dnl;
		dflush;
	}

	SetupMonoTimer();

	// CheckFactors(); 	while(true){}


}

//------------------------------------------------------------------------------

void StartupMessage() {

	Serial.print("   Hi-res One-shot using Timer1\t");
	Serial.print("\n ========================================\n\n");

}

//------------------------------------------------------------------------------

void TestCase_Burst() {

	myT.counter_bottom = 175;

	digitalWrite(13, 1); // set pin 13
	myT.single_shot = true;	// timer will stop itself at next top
	T1_set_prescaler(myT.PSCALE); // starts timer
	// timer resets pin 13 on overflow

	delay(5);
	digitalWrite(13, 1); // set pin 13
	myT.single_shot = false;	// timer will run (observe pin 12)
	T1_set_prescaler(myT.PSCALE); // starts timer
	// timer resets pin 13 in overflow event (interrupt)
	delay(3);

}

//------------------------------------------------------------------------------

void TestCase_OnOff() {

	static byte pass = 0;

	ToggleSyncPin;		// for scope sync
	ulong start_time = micros();

	// trigger one-shot timer to reset later
	//float md1 //  simple action delay
	//float md2 //  wiggle action delay

	if (pass)  // change the handler at each pass
		DoThisLater(md1 * tscale, Action_ClearTestPin);	// ms
	else {
		// global wiggle params 
		DoThisLater(md2 * tscale, Action_ClearAndWigleTestPin);	// ms
	}
	// set Actvity pin here (initiate)
	SetActivityPin;


	if (do_print) {
		
		noInterrupts();
		dpr("<TestCase_OnOff> "); dpr(do_print); dtb; dpr("dly = "); dpr(main_dly); dpr("us"); dnl;
		dtb; dpr("                 md1 = "); dtb; dpr(md1); dpr("ms"); dnl;
		dtb; dpr("                 md2 = "); dtb; dpr(md2); dpr("ms"); dnl;
		dtb; dpr("                wigT = "); dtb; dpr(wigT); dpr("ms"); dnl;
		dtb; dpr("          md1 + wigT = "); dtb; dpr(md2 + wigT); dpr("ms"); dnl;
		dtb; dpr("max(md1, md2 + wigT) = "); dtb; dpr(max(md1, md2 + wigT)); dpr("ms"); dnl;
		dtb; dpr("max(md1, md2 + wigT) = "); dtb; dpr(max(md1, md2 + wigT)); dpr("ms"); dnl;
		dnl;
		dflush;
		do_print--;
		interrupts();

	}

	//if (main_dly < INT16_MAX)
	//	delayMicroseconds(main_dly);  // implementatin is affected by interrupts, not based on time tracking, 
	//else
	//	delay(main_dly/1000);		// allows 

	//ClearAuxPin();

	while (micros() - start_time < main_dly) {}	// delay
	 

	//SetAuxPin;

	pass++;
	pass = pass % 2;
}

//------------------------------------------------------------------------------


void DoThisLater(const float T, voidFuncPtr action) {
	// calculate prescale and divisor -> counter_bottom
	//const float T; // desired millis

	// prime the timer // should be in the class
	{
		FindFactors(T);	// ~90us

		myT.counter_bottom = 65536 - myT.div;

		myT.event_handler = action;		// tell it what to do
		myT.single_shot = true;			// timer will stop itself at next top
	}

	//OCR1B = myT.counter_top -1000;		
	//OCR1A = myT.counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
	//OCR1A = (myT.counter_top-myT.counter_bottom)/2;	  
	//OCR1A = myT.counter_bottom + (myT.counter_top - myT.counter_bottom) / 4;
	//OCR1B = myT.counter_top - (myT.counter_top - myT.counter_bottom) / 4;

	OCR1A = myT.counter_bottom+1;
	OCR1B = myT.counter_top;

	if (do_print) {
		noInterrupts();

		float t_pclk = T1_prescale_factor(myT.PSCALE) / (F_CPU / 1000000.0); // micros

		dpr("<DoThisLater> "); dpr(do_print); dtb; dpr("Action will execute after "); dpr(T); dpr("ms\n");
		dpr("\tp-scale\t"); dpr(T1_prescale_factor(myT.PSCALE)); dpr("\n");
		dpr("\tp-clock\t"); dpr(t_pclk); dpr("\n");
		dpr("\tdiv    \t"); dpr(myT.div); dpr("\n");
		dpr("\tbottom\t"); dpr(myT.counter_bottom); dpr("\n");
		dpr("\tOCR1A\t"); dpr(OCR1A); dpr("\n");
		dpr("\tOCR1B\t"); dpr(OCR1B); dpr("\n");
		dpr("\twidth\t"); dpr(OCR1B - OCR1A); dpr("\n");
		dpr("\n");
		dflush;
		interrupts();

	}


	TCNT1 = myT.counter_bottom;     // preload counter 
	T1_set_prescaler(myT.PSCALE);		// start counting


}

void Action_ClearTestPin() {

	ClearActivityPin;

	{
		if (do_print) {
			dpr("<Action_ClearTestPin> ");dpr(do_print);  dnl;
			dflush;
		}
	}
}


void Action_ClearAndWigleTestPin() {
	// uses global params:
	// float T: total wiggle time in ms
	// byte N: number of cycles
	
	// long wigT: duration of wiggle step in us
	// byte M: total number of wiggle steps (2 per cycle)


	//float t = (T * tscale) / (2 * N); // milliseconds	// 45us if float

	if (do_print) {
		noInterrupts();
		dpr("<Action_ClearAndWigleTestPin> "); dpr(do_print); dtb; dpr(wigStepTime); dpr("ms ");	dpr(M);  dpr(" times");
		dtb; dpr("wigTotalTime"); dpr(wigTotalTime);
		dnl;			
		dflush;
		interrupts();
	}

	ulong start_cycle_time = micros();
	ClearActivityPin; // same as the other action

	// do some more on/off switching that can be observed 
	for (byte i = 0; i < M; i++) {
		//if (wigT < INT16_MAX) delayMicroseconds(wigT); else delay(wigT/1000);
		
		ulong start_step_time = micros();

		while ((micros() - start_step_time < wigStepTime) && (micros() - start_cycle_time < wigTotalTime)) {}

		ToggleActivityPin;

		if (micros() - start_cycle_time > wigTotalTime) break;

	}

}


void loop()
{
	//burst();
	//dpr("\tcall_count\t"); Serial.print(call_count);
	//Serial.print("\n");
	//Serial.flush();

	TestCase_OnOff();

	//while(true){}
}


ISR(TIMER1_OVF_vect) {

	SetTimingPin;
	
	T1_set_prescaler(T1_PSCALE_0); // stop timer clock

	myT.call_count++;

	interrupts();  // allow millis() to update in lengthy handler

	//if(event_handler)	
	myT.event_handler(); // if assigned ...


	if (!myT.single_shot)
		TCNT1 = myT.counter_bottom;   // reload start value if free run

	ClearTimingPin;
}

ISR(TIMER1_COMPA_vect) {

	SetProbePin;
}

ISR(TIMER1_COMPB_vect) {

	ClearProbePin;

}


