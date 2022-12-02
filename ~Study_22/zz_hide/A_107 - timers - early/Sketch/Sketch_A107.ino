#define DBG

//#define ACTIVITY_PIN 13			// green
#define TIMING_PIN 12				// red
#define SYNC_PIN 8					// blue
//#define PROBE_PIN 7 		
//#define AUX_PIN 6 			

#include "utils_test_pins.h"
#include "T1_setup.h"
#include "T1_aux.h"

//#include "Timer_OneShot.h"


myT1_t myT;

bool do_print = true;
typedef void (*funcPtrA)(float T) ;

//Timer_OneShot timerDoNext2;
//
//extern Timer_OneShot timerDoNext;


void setup() {
	// default prep
	{
		Serial.begin(115200);
		Serial.print("\n Running ~Sketch "); DebugPrint("in debug mode"); NL;
		SetupTestPins;
	}

	//TimingLoop(CheckFactors);
	//TimingLoop(FindFactors,4194304/4/4/8);

	TimingLoop();

	
	//CheckFactors();	dnl; dnl;
	//TestFindFactors();

}


void loop() {

}


void TimingLoop(voidFuncPtr funcUnderTest ) {

	funcUnderTest(); do_print = false;

	while (true) {
		ToggleSyncPin;
		dlyMicros(50);

		SetTimingPin;
		funcUnderTest();
		ClearTimingPin;

		dlyMicros(50);

	}
}

void TimingLoop(funcPtrA funcUnderTest, ulong Tus) {

	float T = Tus;

	float Tms = T/1000;

	funcUnderTest(Tms); do_print = false;

	myT.counter_bottom = 65536 - myT.div;
	myT.single_shot = true;			// timer will stop itself at next top

	float t_pclk = T1_prescale_factor(myT.PSCALE) / (F_CPU / 1000000.0); // micros

	// print values
	{
		{
			dtb;
			dpr("T (us)"); dtb;
			dpr("ps    "); dtb;
			dpr("clk   "); dtb;
			dpr("div   "); dtb;
			dpr("botm  "); dtb;
			dpr("T eff "); dtb; dtb;
			dpr("err (1 = 0.001%)"); dtb;
			dpr("\n");
			dtb;
			for (int j = 0; j < 9; j++) { dpr("=======\t"); }
			dpr("\n");
		}
		dtb;
		dpr(T); dtb;
		dpr(T1_prescale_factor(myT.PSCALE)); dtb;
		dpr(t_pclk); dtb;
		dpr(myT.div);  dtb;
		dpr(myT.counter_bottom);  dtb;
		dpr(t_pclk * myT.div); dtb; dtb;
		dpr(abs(t_pclk * myT.div - T) * 100000 / T); dtb;

		dpr("\n");
	}


	while (true) {
		ToggleSyncPin;
		dlyMicros(50);

		SetTimingPin;
		funcUnderTest(Tms);
		ClearTimingPin;

		dlyMicros(50);

	}
}

void TimingLoop() {

	//#define T1_prescale_factor(a)  T1_prescale_factor_old(a) //2104 256
	//#define T1_prescale_factor(a)  T1_prescale_factor_new(a)
	//#define T1_prescale_factor(a)  T1_prescale_factor_def(a)
		//T1_prescale_factor(T1_PSCALE_1);

	volatile float a = 2, b = 3, c=0, d=0;

	while (micros()) {
		ToggleSyncPin;
		//dlyMicros(5);
		//a=-a;
		SetTimingPin;
		{
			//c = a / b;
			c = round(a / b);
			//d = c;
		}
		ClearTimingPin;

		dlyMicros(5);

	}
	//dpr(c);
	//dpr(d);
}


//------------------------------------------------------------------------------
void CheckFactors() {
	uint32_t T, dt = 16;
	byte N = 1;
	float a = 1048576 - (N - 1) * dt;

	for (int i = 0; i < 2 * N - 1; i++) {
		T = a + i * dt;
			SetProbePin;
	//FindFactors(T / 1000.0);
	FindFactors_new(T);
	ClearProbePin;


		myT.counter_bottom = 65536 - myT.div;
		myT.single_shot = true;			// timer will stop itself at next top

		float t_pclk = T1_prescale_factor(myT.PSCALE) / (F_CPU / 1000000.0); // micros


		if (do_print) {

			if (i == 0) {
				dtb;
				dpr("T (us)"); dtb;
				dpr("ps    "); dtb;
				dpr("clk   "); dtb;
				dpr("div   "); dtb;
				dpr("botm  "); dtb;
				dpr("T eff "); dtb; dtb;
				dpr("err (1 = 0.001%)"); dtb;
				dpr("\n");
				dtb;
				for (int j = 0; j < 9; j++) { dpr("=======\t"); }
				dpr("\n");
			}
			dtb;
			dpr(T); dtb;
			dpr(T1_prescale_factor(myT.PSCALE)); dtb;
			dpr(t_pclk); dtb;
			dpr(myT.div);  dtb;
			dpr(myT.counter_bottom);  dtb;
			dpr(t_pclk * myT.div); dtb; dtb;
			dpr(abs(t_pclk * myT.div - T) * 100000 / T); dtb;

			dpr("\n");
		}
	}

}

void TestFindFactors() {

	uint32_t T; byte m = 4;

	auto lst_result = [&]() {
		dtb;
		dpr(T); dtb;
		dpr(T1_prescale_factor(myT.PSCALE)); dtb;
		dpr(myT.div); dtb;
		dpr(myT.tpclk); dtb;
		dnl;
	};
	auto lst_header = [&]() {
		dtb;
		dpr("T (us)"); dtb;
		dpr("ps    "); dtb;
		dpr("div   "); dtb;
		dpr("\n");
		dtb; 	for (int j = 0; j < m; j++) { dpr("=======\t"); } dnl;
	};
	auto lst_separator = [&]() {	dtb; for (int j = 0; j < m; j++) { dpr("-------"); dtb; } dnl;
	};


	lst_header();

	T = 4194304;
	float a = T/1000.0;

	FindFactors(a);

	lst_result();
	lst_separator();

	FindFactors_new(T);

	lst_result();

}


