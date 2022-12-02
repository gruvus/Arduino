/*
* sync cycle on pin 8; probe on pin12
*/

#include "utils.h"
#include "T2_setup.h"

typedef void (*voidFuncPtr)(void);


struct {
	T2_pscale PSCALE = T2_PSCALE_64;	// PSCALE_1,8,32,64,128,256,1024
	byte pscale_N = 0;

	volatile byte counter_bottom = 0; // uint8_t
	volatile bool single_shot = false;
	volatile unsigned int call_count = 0;
	volatile voidFuncPtr event_handler;


} myT;


void SetupMonoTimer() {
	// initialize timer2 in NormalVar mode
	// generates overflow interrupt at 255 


	noInterrupts();           // disable all interrupts
	TCCR2A = 0; 	TCCR2B = 0;		TIMSK2 = 0;

	// set interrupts
	T2_set_intmask(1, 1, 1); // (comparators A,B only for test) , overflow

	// set Waveform Generation Mode
	T2_set_wfgmode(T2_WGM_NORMAL);
	// set Compare Output Mode
	T2_set_comA(T2_COM_TOGGLE);	// observe OC2A on pin 11
	T2_set_comB(T2_COM_TOGGLE);	// observe OC2B on pin 3

	// set counting cycle/frequency
	const byte counter_top = 255; // fixed in Normal mode

	byte div = 256;			// with prescaler :64 -> 16MHz/64/256 = 977Hz (1024 us sycle)
	//byte div = 250;			// with prescaler :64 -> 16MHz/64/250 = 1kHz
	//byte div = 125;			// with prescaler :128 -> 16MHz/128/125 = 1kHz

	div = 10;


	myT.counter_bottom = 255 - div + 1;		// load start value on overflow (at top)

	{
		Serial.print("\n\tSet frequency\tBottom\tTop\tSteps");
		Serial.print("\n\t             \t");
		Serial.print(myT.counter_bottom);	Serial.print("\t");
		Serial.print(counter_top);	Serial.print("\t");
		Serial.print(counter_top - myT.counter_bottom + 1);	Serial.print("\t");
		Serial.print("\n\n");
		Serial.flush();
	}

	// set compare values
	//OCR2A = counter_bottom + 120;	  // observe on pin 11
	OCR2A = counter_top;	  
	OCR2B = myT.counter_bottom + 1;	  // counter_bottom match "event" not triggered if OC interrupts enabled
	//OCR2B = (counter_bottom + counter_top)/2;	  
	//OCR2B = counter_top - 1;
	byte width = OCR2A - OCR2B;

	{
		Serial.print("\n\tSet A,B\t\tA\tB\tWidth");
		Serial.print("\n\t       \t\t");
		Serial.print(OCR2B);	Serial.print("\t");
		Serial.print(OCR2A);	Serial.print("\t");
		Serial.print(width);	Serial.print("\t");
		Serial.print("\n\n");
		Serial.flush();
	}

	// set prescaler and start the counter
	//set_prescaler(PSCALE); // PSCALE_1,8,32,64,128,256,1024

	T2_set_prescaler(T2_PSCALE_0); // do not start yet

//	noInterrupts();           // disable all interrupts

	interrupts();             // enable all interrupts

	// can observe OC2A/B on pins 11/3

	pinMode(11, OUTPUT);	// OC2A
	pinMode(3, OUTPUT);		// OC2B
}

unsigned long start_time = 0;

void setup()
{
	// test pins
	pinMode(13, OUTPUT);		// built-in LED  //pin 13: PORTB5 PINB5
	pinMode(12, OUTPUT);		// "probe" pin   //pin 12: PORTB4 PINB4
	pinMode(8, OUTPUT);			// "probe" pin   //pin 8: PORTB0 PINB0


	Serial.begin(115200);	Serial.print("\n");

	StartupMessage();

	myT.pscale_N = T2_prescale_factor(myT.PSCALE);

	myT.event_handler = Action_Nothing;;

	{
		Serial.print("\n");
		Serial.print("\tevent_handler\t");	Serial.print((unsigned long)myT.event_handler);
		Serial.print("\n");
		Serial.print("\Action_Nothing\t");		Serial.print((unsigned long)Action_Nothing);
		Serial.print("\n");
		Serial.print("\Action_ClearTestPin\t");	Serial.print((unsigned long)Action_ClearTestPin);
		Serial.print("\n");
	}

	myT.single_shot = true;

	SetupMonoTimer();

}

void StartupMessage() {

	Serial.print(" One-shot Timer Execise\t");
	Serial.print("\n ========================================\n");
	Serial.print("   Using Timer2 \n");

}


void TestCase_Burst() {

	myT.counter_bottom = 175;

	digitalWrite(13, 1); // set pin 13
	myT.single_shot = true;	// timer will stop itself at next top
	T2_set_prescaler(myT.PSCALE); // starts timer
	// timer resets pin 13 on overflow

	delay(5);
	digitalWrite(13, 1); // set pin 13
	myT.single_shot = false;	// timer will run (observe pin 12)
	T2_set_prescaler(myT.PSCALE); // starts timer
	// timer resets pin 13 in overflow event (interrupt)
	delay(3);

}

void TestCase_OnOff() {

	static voidFuncPtr action;
	static byte pass = 0;
	// set pin13 here, trigegr one-shot timer to reset later 
	digitalWrite(13, 1); // set pin 13

	if (pass)  // change the handler
		DoThisLater(50, Action_ClearAndWigleTestPin);
	else
		DoThisLater(100, Action_ClearTestPin);

	delay(1);
	pass++;
	pass = pass % 2;
	digitalWrite(8, pass); // for scope sync
}

void DoThisLater(const byte t, voidFuncPtr action) {

	// calculate prescale and divisor -> counter_bottom
	myT.counter_bottom = 256 - t;

	myT.event_handler = action;		// tell it what to do
	myT.single_shot = true;			// timer will stop itself at next top

	TCNT2 = myT.counter_bottom;     // preload counter 
	T2_set_prescaler(myT.PSCALE);		// start counting
}

void Action_ClearTestPin() {

	//digitalWrite(13, 0); // clear pin 13 //
	PORTB &= ~(1 << PORTB5);	// clear pin 13
}


void Action_ClearAndWigleTestPin() {

	//digitalWrite(13, 0); // clear pin 13 //
	PORTB &= ~(1 << PORTB5);	// clear pin 13
	delayMicroseconds(50);
	digitalWrite(13, 1); // set pin 13 
	delayMicroseconds(50);
	digitalWrite(13, 0); // clear pin 13
	delayMicroseconds(50);
	digitalWrite(13, 1); // set pin 13
	delayMicroseconds(50);
	digitalWrite(13, 0); // clear pin 13

}


void loop()
{
	//burst();
	//Serial.print("\tcall_count\t"); Serial.print(call_count);
	//Serial.print("\n");
	//Serial.flush();

	TestCase_OnOff();

}


ISR(TIMER2_OVF_vect) {

	//PORTB |= (1 << PORTB0);		// set pin 8


	myT.call_count++;
	//if(event_handler)	
	myT.event_handler(); // if assigned ...

	if (myT.single_shot) T2_set_prescaler(T2_PSCALE_0); // stop timer clock
	TCNT2 = myT.counter_bottom;   // reload start value 

	//PORTB &= ~(1 << PORTB0);	// clear pin 8

}

ISR(TIMER2_COMPA_vect) {
		//PORTB &= ~(1 << PORTB4);	// clear pin 12
		PORTB |= (1 << PORTB4);		// set pin 12
}

ISR(TIMER2_COMPB_vect) {

	//PORTB |= (1 << PORTB4);		// set pin 12
	PORTB &= ~(1 << PORTB4);	// clear pin 12
}


