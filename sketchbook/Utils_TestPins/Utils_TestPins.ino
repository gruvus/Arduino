#define DBG

#define ACTIVITY_PIN 13			// green
#define TIMING_PIN 12				// red
#define SYNC_PIN 8					// blue
#define PROBE_PIN 7 		
#define AUX_PIN 6 			

#include "utils_test_pins.h"



void setup() {
	// default prep
	{
		Serial.begin(115200);
		lst("\nTestPins - development "); dpr("(Debug mode)"); nl;
		lstm("=", 40);	nl;
		SetupTestPins;
	}

	ClearActivityPin;

	//showTestPinsInfo();

	portH_toggle_problem();


	//dstop;

	noInterrupts();
}



void loop() {

	static byte pass = 0;
	ToggleSyncPin;

	ToggleActivityPin;		//	D13
	ToggleActivityPin;		//	D13

	ToggleTimingPin;		//	D12
	ToggleTimingPin;

	ToggleProbePin;
	ToggleProbePin;

	//PIND = bit(PIND7);	//	D10  //  bit(PIND7) = (1 << PIND7)
//PIND = (1 << PIND7);	// 

	ToggleAuxPin;
	ToggleAuxPin;

}


void TimingLoop() {

	volatile float a = 2, b = 3, c = 0, d = 0;

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

}


#ifdef ARDUINO_AVR_MEGA2560

void portH_toggle_problem() {
	/* 11/10/22
	Problem: attemping to use both ToggleProbePin and ToggleAuxPin on caused both pisn to toggle (actually at any PINH |= (1 << PINHx))
	* cause: using |= means read then OR then write; reading PINH seems to return 255 so all bitts would be set to 1
	* solution: using "write 1 to PINxn" to toggle should not use |= rather just =; it also faster
	* Observation: on PORTB, E, G toggling this way takes only 1 clock cycle; takes 2 tck on PORTH
	*
	* 11/11/22: reading PINH returns 0 ... so not always 255 - above correction is valid regardless 
	*/

	// setup
	{
		pinMode(11, OUTPUT);
		pinMode(10, OUTPUT);
		pinMode(9, OUTPUT);
		pinMode(5, OUTPUT);
		pinMode(4, OUTPUT);
		pinMode(3, OUTPUT);
		pinMode(2, OUTPUT);

		for (byte pin = 14; pin <= 21; pin++) pinMode(pin, OUTPUT);


		//PORTH = 0xff;


		dtb; dpr(PINB);
		dtb; dpr(PINE);
		dtb; dpr(PING);
		dtb; dpr(PINH);
		dnl;
		dflush;

	}

	while (true) {
		static byte pass = 0;
		//digitalWrite(activity_pin, pass);

		ToggleActivityPin;		//	D13
		ToggleTimingPin;		//	D12
		ToggleTimingPin;

		PINB = (1 << PINB5);	//	D11
		PINB = (1 << PINB5);	// 

		PINB = (1 << PINB4);	//	D10
		PINB = (1 << PINB4);	// 

		// PINH |= (1 << PINH6);	// D9			// !!! toggle on any pin on port H toggles all
		//PINH = 64;	// D9			// this works ok; alos onpy 2 tck
		//bitSet(PINH, PINH6);			// also does the |= which means read first // reading PORTH (sometimes) returns FF => toggle all

		PINH = bit(PINH6);		// D9		
		PINH = bit(PINH6);


		// toggle should not do |=, just =  !!! no neer for the OR; writing 0 has no effect

		//PORTH &= ~(1 << PORTH6);	//	D9	
		//PORTH |= (1 << PORTH6);		//	D9

		PINH = (1 << PINH5);	// D8
		PINH = (1 << PINH5);	// D8
		//PORTH &= ~(1 << PORTH5);	//	D8
		//PORTH |= (1 << PORTH5);		//	D8


		PINH = (1 << PINH4);		// D7
		PINH = (1 << PINH4);		// D7
		//PORTH &= ~(1 << PORTH4);	//	D7
		//PORTH |= (1 << PORTH4);		//	D7

		PINH = (1 << PINH3);		// D6
		PINH = (1 << PINH3);		// D6
		//PORTH &= ~(1 << PORTH3);	//	D6
		//PORTH |= (1 << PORTH3);		//	D6


		PINE = (1 << PINE3);	// D5
		PINE = (1 << PINE3);	// D5 

		PING = (1 << PING5);	// D4 
		PING = (1 << PING5);	// D4 

		PINE = (1 << PINE5);	// D3 
		PINE = (1 << PINE5);	// D3 

		PINE = (1 << PINE4);	// D2 
		PINE = (1 << PINE4);	// D2 

		pass++;
		pass = pass % 2;
	}


}

#endif // 
