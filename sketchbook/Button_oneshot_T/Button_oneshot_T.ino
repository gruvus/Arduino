
#define ACTIVITY_PIN 13			// green
//#define TIMING_PIN 12			// red

#define SYNC_PIN 8				// blue
//#define PROBE_PIN 12 		
//#define AUX_PIN 6 			

#define AUX_PIN 12 			

#include "utils_test_pins.h"
//#include "utils.h"

#include "Timer_OneShot.h"


// ***  application parameters

const int DEBOUNCE_TIME_ms = 20;	//const long DEBOUNCE_TIME_us = DEBOUNCE_TIME_ms * 1000L;

volatile int event_count = 0;

volatile ulong event_time = 0;
volatile byte button_value;		// unfiltered button reading
volatile int event_count_all = 0;

int Button_stable_state;

const byte buttonPin = 3;


OneShotBase& myTmr8 = myOneShot8_onT2;
OneShotBase& myTmr16 = myOneShot16_onT1;

OneShotBase& myTmr = myTmr16;



void setup() {

	//default prep
	{
		Serial.begin(115200);
		lst(" Running "); lst("<Resolve button state using TimerOneShot Class> "); dpr("in debug mode"); nl;
		dpr(__cplusplus); lst(" ========================================\n\n");
		SetupTestPins;
	}

	pinMode(buttonPin, INPUT_PULLUP);

	noInterrupts();

	button_value = digitalRead(buttonPin);
	Button_stable_state = button_value;
	digitalWrite(activity_pin, button_value);
	digitalWrite(aux_pin, button_value);


	attachInterrupt(digitalPinToInterrupt(buttonPin), button_event_change, CHANGE);

	myTmr.Initialize(DEBOUNCE_TIME_ms*1000, CheckButtonState);	//
	myTmr.show_config();

	interrupts();

}

void loop() {
  
}


void CheckButtonState() {

	// things have been quiet for the debounce interval (DEBOUNCE_TIME_us)
	// we have a "stable" reading if we got here
	// no need for local copies of volatile variables (interrupts are disabled)

		event_count = 0;				// mark "stable" reading

	// did the stable state change?
	if (Button_stable_state != button_value)
	{
		Button_stable_state = button_value;	// update "official" state
		// we have a state change, do something based on the button state

		if (Button_stable_state) SetActivityPin; else ClearActivityPin;// "publish" button state
		
		//digitalWrite(statePin, Button_stable_state);			

		//digitalWrite(probePin, Button_stable_state);		// sync probe LED to button state //for demo

		if (Button_stable_state) SetAuxPin; else ClearAuxPin; // sync probe LED to button state //for demo

		//noInterrupts();
		event_count_all = 0;
		//interrupts();

	}

}
	

void button_event_change() {

	SetSyncPin;

	{ // core function, the rest is for study // ~5uS (including timing probe overhead)
		event_time = micros();	 //time stamp
		event_count++;
		// get momentary state
		// button_value = digitalRead(buttonPin); // adds ~3uS
		//button_value = (PIND >> PIND2) & 0x01;  // 
		button_value = readInterruptPin(buttonPin);  // 

	}

	//myTmr.DoLater(CheckButtonState, DEBOUNCE_TIME_us);
	myTmr.Restart(); // event handler was assigend at initialization

	{	// for the flickering LED, not core function // ~1.5uS
		event_count_all++;
		//if (button_value) PORTB |= (1 << PORTB4); else PORTB &= ~(1 << PORTB4);
		//PINB |= (1 << PINB4); // toggle probe pin 12 // more visible this way 
		ToggleAuxPin;
	}

	ClearSyncPin;
}

byte readInterruptPin(const byte pin) {
	switch (pin) {
	case 2:
		return (PIND >> PIND2) & 0x01;
	case 3:
		return (PIND >> PIND3) & 0x01;
	default:
		dpr("<readInterruptPin> invalid interrupt pin: "); dpr(pin); dnl;
	}
}