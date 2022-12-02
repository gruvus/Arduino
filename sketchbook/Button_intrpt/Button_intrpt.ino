/*
 * normal-open switch on interruptPin to GND
 * 
 * (green) LED on pin statePin: display stable button state (debounced)
 * (red) LED on probePin: show flickering with contact bouncing  
 * 
 */

// ***  hardware configuration

#define TIMING_PIN 8		// defines timingPin, if used

//#define ACTIVITY_PIN 13			// green
//#define TIMING_PIN 12			// red
//#define SYNC_PIN 8				// blue
//#define PROBE_PIN 7 		
//#define AUX_PIN 6 			

#include "utils_test_pins.h"


const byte interruptPin = 2;
const byte statePin = 13;
const byte probePin = 12;

#define TRACE_on
//#define TEST_MODE

#ifdef TRACE_on
#define TEST_MODE
#endif // 

#ifndef TEST_MODE
#undef TIMING_PIN
#endif

#include "utils.h"


// ***  application parameters

const int DEBOUNCE_TIME_ms = 20;	const long DEBOUNCE_TIME_us = DEBOUNCE_TIME_ms * 1000L;
const int FLICKER_TIME_ms = 10;		const long FLICKER_TIME_us = FLICKER_TIME_ms * 1000L;

volatile int event_count = 0;

volatile ulong event_time = 0;
volatile int button_value;		// unfiltered button reading
#ifdef TEST_MODE
volatile int event_count_all = 0;
#endif
int Button_stable_state;

void setup() {
#ifdef TRACE_on
	Serial.begin(115200);
	Serial.print("\n\n ===== Resolve Button state using external interrupts =====\n\n");
	Serial.print("\tDebounce time: ");
	Serial.print(DEBOUNCE_TIME_ms); Serial.print("mS\n\n");
	Serial.flush();
#endif
	pinMode(interruptPin, INPUT_PULLUP);
	pinMode(statePin, OUTPUT);

	SetupTestPins;

//	noInterrupts();
	button_value = digitalRead(interruptPin);
	Button_stable_state = button_value;
	digitalWrite(statePin, button_value);

#ifdef TEST_MODE
	pinMode(probePin, OUTPUT);
	digitalWrite(probePin, button_value);
#endif

	attachInterrupt(digitalPinToInterrupt(interruptPin), button_event_change, CHANGE);
//	interrupts();
}

void loop() {  // observing button state

	int ev_count, btn_val;
	ulong now, ev_time;	long time_since_change;

#ifdef TEST_MODE
	int ev_cnt_all;
#endif
	
	auto print_trace_header = []() {
#ifdef TRACE_on
		static byte pass = 0;

		if (pass == 0) {
			//print header
			pass = 1;
			Serial.print("  ");	Serial.print("Now        \t");Serial.print("Event time \t");Serial.print("Elapsed    \t");
			Serial.print("Events (last)\t");Serial.print("Events (all)\t");
			Serial.print("Button  \t");
			Serial.print("\n");
			delay(1000);
			Serial.print("  ");	Serial.print("===        \t"); Serial.print("========= \t"); Serial.print("=======    \t");
			Serial.print("=============\t"); Serial.print("============\t");
			Serial.print("======  \t");
			Serial.print("\n");
		}
#endif // TRACE_on
	};
	auto print_trace_line = [&]() {
#ifdef TRACE_on
		Serial.print("  ");

		//Serial.print("Now        \t");
		Serial.print(now); Serial.print("\t");

		//Serial.print("Event time \t");
		Serial.print(event_time); Serial.print(" \t");

		//Serial.print("Elapsed    \t");
		Serial.print(time_since_change / 1000.0); Serial.print(" ms\t");

		//Serial.print("Events (last)\t");
		Serial.print(ev_count); Serial.print(" \t\t");

		//Serial.print("Events (all)\t");
		Serial.print(ev_cnt_all); Serial.print(" \t\t");

		//Serial.print("Button  \t");
		Serial.print(Button_stable_state); Serial.print("  \t");

		Serial.print("\n");
		Serial.flush();
#endif // TRACE_on
	};

	print_trace_header();

	// Main body
	// make local copies of volatile variables
	noInterrupts();
	ev_count = event_count;		// number of change events since last stable reading
	ev_time = event_time;		// time stamp of last change
	btn_val = button_value;		// button value after last change
	interrupts();

	// any changes since last "stable" reading? 
	if (event_count > 0) {
		// was it long ago?
		now = micros();
		time_since_change = now - ev_time;
		if (time_since_change > DEBOUNCE_TIME_us) {
			// we have a "stable" reading
			noInterrupts();
			{
				btn_val = button_value;			// get button state
				event_count = 0;				// mark "stable" reading
#ifdef TEST_MODE
				ev_cnt_all = event_count_all;	// copy cumulative count, need for report (may reset before)
#endif
			}
			interrupts();

			// did the stable state change?
			if (Button_stable_state != btn_val)
			{
				Button_stable_state = btn_val;	// update "official" state
				// we have a state cahange, do something based on the button state
				digitalWrite(statePin, Button_stable_state);			// "publish" button state

#ifdef TEST_MODE
				digitalWrite(probePin, Button_stable_state);		// sync probe LED to button state //for demo
				noInterrupts();
				event_count_all = 0;
				interrupts();
#endif

				print_trace_line();

			}
		}
#ifdef TEST_MODE
		if (time_since_change > FLICKER_TIME_ms) digitalWrite(probePin, Button_stable_state);		// sync probe LED to button state
#endif

		}

	delay(1);
}

void button_event_change() {

	SetTimingPin;
	{ // core function, the rest is for study // ~5uS (including timing probe overhead)
		event_time = micros();	 //time stamp
		event_count++;
		// get momentary state
		// button_value = digitalRead(interruptPin); // adds ~3uS
		button_value = (PIND >> PIND2) & 0x01;
	}
#ifdef TEST_MODE
	{	// for the flickering LED, not core function // ~1.5uS
		event_count_all++;
		//if (button_value) PORTB |= (1 << PORTB4); else PORTB &= ~(1 << PORTB4);
		PINB |= (1 << PINB4); // toggle probe pin 12 // more visible this way 
	}
#endif
	ClearTimingPin;
}
