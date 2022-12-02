

// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER2_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER2_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER2_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)


void TestPrint() {
	Serial.print("Using Timer2 in Normal mode\n\n");
	Serial.print("MICROSECONDS_PER_TIMER2_OVERFLOW\t"); Serial.print(MICROSECONDS_PER_TIMER2_OVERFLOW);
	Serial.print("\n");

	Serial.print("clockCyclesPerMicrosecond\t"); Serial.print(clockCyclesPerMicrosecond());
	Serial.print("\n");

	Serial.print("MILLIS_INC\t"); Serial.print(MILLIS_INC);	Serial.print("\n");
	Serial.print("FRACT_INC\t"); Serial.print(FRACT_INC);	Serial.print("\n");
	Serial.print("FRACT_MAX\t"); Serial.print(FRACT_MAX);	Serial.print("\n");
	Serial.print("FRACT_MAX\t"); Serial.print(FRACT_MAX, BIN);	Serial.print("\n");
}

void StartupMessage() {

	Serial.print("MicrosAlt\t");
	Serial.print("\n========================================\n");
	TestPrint();
}


volatile unsigned long timer2_overflow_count = 0;
volatile unsigned long timer2_millis = 11;
//static unsigned char timer2_fract = 0;


ISR(TIMER2_OVF_vect) {
	PINB |= (1 << PINB5); // fast toggle pin 13 built-in LED
	PORTB |= (1 << PORT4); // set pin 12

//.........................................................................
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)

	static unsigned char timer2_fract = 0;

	unsigned long m = timer2_millis;
	unsigned char f = timer2_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer2_fract = f;
	timer2_millis = m;
	timer2_overflow_count++;
	
	//.........................................................................
	PORTB &= ~(1 << PORT4); // clear pin 12

}


unsigned long millis2()
{
	unsigned long m;
	uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
	m = timer2_millis;
	SREG = oldSREG;
	return m;
}

//void yield() 
//// called from within the delay() function every 3-4us, alows non-blocking
//// "weak" function, can be reimplemented ; does nothing in default  
//{ 
//	PINB |= (1 << PINB4); // fast toggle pin 12
//}


unsigned long micros2() {

	uint8_t oldSREG = SREG;  // save state
	cli();		// disable interrupts

	uint8_t t = TCNT2;
	unsigned long m = timer2_overflow_count;

	// possible miss? (see https://ucexperiment.wordpress.com/2012/03/17/examination-of-the-arduino-micros-function/)
	// "check for the potential rare instance of an interrupt occurring during the micros() function call"
#ifdef TIFR2
	if ((TIFR2 & _BV(TOV2)) && (t < 255)) { // how can that happen? the flag is reset when the IRS is called (according to the ATMEL manula)
		m++;
		ovflag_count++;
	}
#else
	if ((TIFR & _BV(TOV0)) && (t < 255))
		m++;
#endif

	SREG = oldSREG;	// restore state (also enables interrupts after the next instruction)

	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond()) + 11070;
}







