//#define DBG

#define ACTIVITY_PIN 13			// green
//#define TIMING_PIN 12			// red
#define SYNC_PIN 8				// blue
//#define PROBE_PIN 7 		
#define AUX_PIN 6 			

#include "utils_test_pins.h"
//#include "utils.h"

#include "Timer_OneShot.h"


#ifdef ARDUINO_AVR_UNO
const char boardName[] = "UNO";
#endif

#ifdef ARDUINO_AVR_MEGA2560
const char boardName[] = "MEGA";
#endif

// ***** <Parameters> section : test case parameters *******
namespace params {

	const float tscale = 1;		// time scale :1ms | 1 for o-scope // high jitter below 0.5

	const float tscale_us = tscale * 1000;	// in microseconds

	const float main_cycle = 1;		// period of main repeat cycle in ms
	const float md1 = 0.7;		// simple action delay
	const float md2 = 0.3;		// wiggle action delay
	const float wigT = 0.3;		// total wiggle time in ms
	const byte N = 2;		// number of wiggle cycles

	// check minimum pause after action pause = main_cycle - max(md1, md2 + wigT);

	//..... pre calculations

	const long main_dly = main_cycle * tscale_us;

	const byte M = 2 * N; 		// total number of wiggle steps (2 per cycle)
	// duration of wiggle step in us
	const ulong wigStepTime = (wigT * tscale_us) / M; // micros
	// float t = (T * tscale) / (2 * N); // milliseconds	// 45us if float
	const ulong wigTotalTime = wigT * tscale_us;
}
// **** end of <Parameters> section ***************

byte do_print = 2;

//extern OneShot16_onT1  myOneShot16_onT1;


OneShotBase& myTmr8_2 = myOneShot8_onT2;
OneShotBase& myTmr16_1 = myOneShot16_onT1;
#ifdef ARDUINO_AVR_MEGA2560
OneShotBase& myTmr16_3 = myOneShot16_onT3;
OneShotBase& myTmr16_4 = myOneShot16_onT4;
OneShotBase& myTmr16_5 = myOneShot16_onT5;
#endif

OneShotBase& myTmr = myTmr16_5;


//-------------------------------------------------------
void setup() {
	 //default prep
	{
		Serial.begin(115200);
		lst(" Running "); lst("_TimerClasses_dev "); dpr("in debug mode"); nl;
		tab; lst("OneShot device using Timers 1, 2, 3, 4, 5"); nl;
		dpr(boardName); dnl;
		dpr(__cplusplus);lst(" ========================================\n\n");

		SetupTestPins;
	}

	myTmr.Initialize(1000);
	myTmr.show_config();

	float t = 3333333;  // 16.384    4194.3047

	goto exit;

	//myTmr.SetDuration(t * 1);
	//myTmr.show_config();
	//myTmr.SetDuration(t * 8 );
	//myTmr.show_config();
	//myTmr.SetDuration(t * 64 );
	//myTmr.show_config();
	//myTmr.SetDuration(t * 256 );
	//myTmr.show_config();
	myTmr.SetDuration(t * 1024 );
	myTmr.show_config();

	dstop;


exit:

	dpr(" ========================================\n\n");

	dflush;

}

//-------------------------------------------------------
void loop() {

	const uint32_t t = 4194304;  // 4194304

	//TestCase_OnOff_1();

	TestCase_OnOff_2();

	//Test_SetDuration(t, t+1);

}

//-------------------------------------------------------
void Test_SetDuration(uint32_t A, uint32_t B) {
	static byte pass = 0;
	
	noInterrupts();

	ToggleSyncPin;		// for o-scope sync

	SetActivityPin;

	if (pass) {
		myTmr.SetDuration(B);
	}
	else {
		myTmr.SetDuration(A);
	}
	ClearActivityPin;
	
	interrupts();

	pass++;
	pass = pass % 2;

}

//-------------------------------------------------------
void TestCase_OnOff_2() {
	using namespace params;

	static byte pass = 0;

	noInterrupts();

	ToggleSyncPin;		// for scope sync


	ToggleAuxPin;


	ulong start_time = micros();


	// set actvity pin here (initiate)
	SetActivityPin;

	if (pass)  // change the handler at each pass
		myTmr.DoLater(Action_ClearTestPin, md1 * tscale_us );	// us
	else {
		// global wiggle params 
		myTmr.DoLater(Action_ClearAndWigleTestPin, md2 * tscale_us );	// us
	}

	interrupts();

	if (do_print) {
		noInterrupts();

		myTmr.show_config();

		interrupts();

	}


	if (do_print) {
		noInterrupts();
		dpr("<TestCase_OnOff_2> "); dpr(do_print); dnl;
		dtb; dpr("                 dly = "); dpr(main_dly); dpr("us"); dnl;
		dtb; dpr("                 md1 = "); dpr(md1 * tscale); dpr("ms"); dnl;
		dtb; dpr("                 md2 = "); dpr(md2 * tscale); dpr("ms"); dnl;
		dtb; dpr("                wigT = "); dpr(wigT * tscale); dpr("ms"); dnl;
		dtb; dpr("          md1 + wigT = "); dpr((md2 + wigT) * tscale); dpr("ms"); dnl;
		dtb; dpr("max(md1, md2 + wigT) = "); dpr(max(md1, md2 + wigT) * tscale); dpr("ms"); dnl;
		dnl;
		dflush;
		do_print--;
		interrupts();
	}


	//if (main_dly < INT16_MAX)
	//	delayMicroseconds(main_dly);  // implementation is affected by interrupts, not based on time tracking, 
	//else
	//	delay(main_dly/1000);		// allows 

	ClearAuxPin;

	while (micros() - start_time < main_dly) {}	// delay


	SetAuxPin;

	pass++;
	pass = pass % 2;
}

//-------------------------------------------------------
void TestCase_OnOff_1() {
	using namespace params;

	static byte pass = 0;

	//noInterrupts();

	ToggleSyncPin;		// for scope sync
	ulong start_time = micros();

	if (pass)
		myTmr.DoLater(Action_ClearTestPin, md1 * tscale_us );	//
	else
		myTmr.DoLater( Action_ClearTestPin);	

		// set Actvity pin here (initiate)
	SetActivityPin;

	//interrupts();


	if (do_print) {

		noInterrupts();
		dpr("<TestCase_OnOff_1> "); dpr(do_print); dnl;
		dtb; dpr("dly = "); dpr(main_dly); dpr("us"); dnl;
		dtb; dpr("md1 = "); dpr(md1 * tscale); dpr("ms"); dnl;
		dnl;
		dflush;
		do_print--;
		interrupts();

	}

	while (micros() - start_time < main_dly) {}	// delay

	pass++;
	pass = pass % 2;
}

//-------------------------------------------------------
void Action_ClearTestPin() {

	ClearActivityPin;

	//{
	//	if (do_print) {
	//		dpr("<Action_ClearTestPin> "); dpr(do_print);  dnl;
	//		dnl;
	//		dflush;
	//	}
	//}
}

//-------------------------------------------------------
void Action_ClearAndWigleTestPin() {
	// uses global params:
	// float T: total wiggle time in ms
	// byte N: number of cycles

	using namespace params;
	// long wigT: duration of wiggle step in us
	// byte M: total number of wiggle steps (2 per cycle)


	//float t = (T * tscale) / (2 * N); // milliseconds	// 45us if float

	if (do_print) {
		noInterrupts();
		dpr("<Action_ClearAndWigleTestPin> "); dpr(do_print); dtb; dpr(wigStepTime); dpr("ms "); dpr(M);  dpr(" times");
		dtb; dpr("wigTotalTime: "); dpr(wigTotalTime);
		dnl; dnl;
		dflush;
		interrupts();
	}

	ulong start_cycle_time = micros();
	ClearActivityPin; // same as the other action

	// do some more on/off switching that can be observed 
	for (byte i = 0; i < M; i++) {
		//if (wigT < INT16_MAX) delayMicroseconds(wigT); else delay(wigT/1000);

		ulong start_step_time = micros();

		//while ((micros() - start_step_time < wigStepTime) && (micros() - start_cycle_time < wigTotalTime)) {}
		ulong now;
		bool done, overdone;
		do {
			now = micros();
			done = now - start_step_time >= wigStepTime;
			overdone = now - start_cycle_time >= wigTotalTime;
		} while (!(done || overdone));


		ToggleActivityPin;

		if (overdone) break;

	}

}



