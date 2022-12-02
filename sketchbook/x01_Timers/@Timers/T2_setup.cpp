
/*
* TCCR2A	7		6		5		4		3	2	   1	   0
*		COM2A1	COM2A0	COM2B1	COM2B0		-	-	WGM21	WGM20
*		   r/w	   r/w	   r/w	   r/w		r	r	  r/w	  r/w
*
*	COM2A1:2 for non-PWM modes
*		00 - normal port operation, OC2A disconnected
*		01 - toggle OC2A on compare match
*		10 - clear
*		11 - set
*
*	OC2A and OC2B connect to pins D11 and D3
*	D11 and D3 should be configured as OUTPUT after the timer/counter
*
*	WGM22:0
*		000 - normal
*		010 - CTC
*
* TCCR2B	7		6		5	4		3		  2		  1		  0
*		FOC2A	FOC2B		-	-	 WGM22		CS22	CS21	CS20
*			w		w		r	r		r		 r/w	 r/w	 r/w
*
*	CS22:0
*		000 - stop				100 - div by   64
*		001 - div by  1			101 - div by  128
*		010 - div by  8			110 - div by  256
*		011 - div by 32			111 - div by 1024
*
* TIMSK2	7	6	5	4	3		2		1		0
*			-	-	-	-	-	OCIE2B	OCIE2A	 TOIE2
*			r	r	r	r	r	   r/w	   r/w	   r/w
*
*	TCNT2 - Timer/Counter Register			TCNT2[7:0]
*	OCR2A - Output Compare Register A		OCR2A[7:0]
*	OCR2B - Output Compare Register B		OCR2B[7:0]
*
*
*/

#include "T2_setup.h"


//enum T2_wfgmode { T2_WGM_NORMAL, T2_WGM_CTC };
void T2_set_wfgmode(T2_wfgmode wfg_mode) {

	// set Waveform Generation Mode
	switch (wfg_mode)
	{
	case T2_WGM_CTC:
		TCCR2B |= (0 << WGM22); TCCR2A |= ((1 << WGM21) | (0 << WGM20));	// 010 - CTC
		break;

	case T2_WGM_NORMAL:
	default:
		TCCR2B |= (0 << WGM22); TCCR2A |= ((0 << WGM21) | (0 << WGM20));	// 000 - normal (default)
	}
	//TCCR2B |= (0 << WGM22); TCCR2A |= ((1 << WGM21) | (0 << WGM20));	// 010 - CTC
	//TCCR2B |= (0 << WGM22); TCCR2A |= ((0 << WGM21) | (0 << WGM20));	// 000 - normal (default)

} //=====================================================

void T2_set_intmask(byte oc_A, byte oc_B, byte ovf) {
	//set interrupts
	TIMSK2 |= ((oc_A << OCIE2A) | (oc_B << OCIE2B) | (ovf << TOIE2));   // set overflow and copmpares interrupts

	//TIMSK2 = ((1 << OCIE2A) | (1 << OCIE2B) | (1 << TOIE2));   // enable overflow and copmpares interrupts
} //=====================================================

//enum T2_pscale { PSCALE_1, PSCALE_8, PSCALE_32, PSCALE_64, PSCALE_128, PSCALE_256, PSCALE_1024 };
void T2_set_prescaler(T2_pscale prescale_selector) {

	// set prescaler and start the counter

	switch (prescale_selector) {
	case T2_PSCALE_0:
		TCCR2B |= ((0 << CS22) | (0 << CS21) | (0 << CS20)); 	// sets prescaler at 0			stop
		break;
	case T2_PSCALE_1:
		TCCR2B |= ((0 << CS22) | (0 << CS21) | (1 << CS20)); 	// sets prescaler at 1			16MHz =>  62.5ns
		break;
	case T2_PSCALE_8:
		TCCR2B |= ((0 << CS22) | (1 << CS21) | (0 << CS20)); 	// sets prescaler at 8			 2MHz => 500ns
		break;
	case T2_PSCALE_32:
		TCCR2B |= ((0 << CS22) | (1 << CS21) | (1 << CS20)); 	// sets prescaler at 32		   500kHz =>  2us
		break;
	case T2_PSCALE_64:
		TCCR2B |= ((1 << CS22) | (0 << CS21) | (0 << CS20)); 	// sets prescaler at 64		   250kHz =>  4us
		break;
	case T2_PSCALE_128:
		TCCR2B |= ((1 << CS22) | (0 << CS21) | (1 << CS20)); 	// sets prescaler at 128	   125kHz =>  8us
		break;
	case T2_PSCALE_256:
		TCCR2B |= ((1 << CS22) | (1 << CS21) | (0 << CS20)); 	// sets prescaler at 256	   62.5kHz => 16us
		break;
	case T2_PSCALE_1024:
	default:
		TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));	   // sets prescaler at 1024	  15,625Hz => 64us
		break;

	}

	//TCCR2B |= ((0 << CS22) | (0 << CS21) | (1 << CS20)); 	// sets prescaler at 1			16MHz =>  62.5ns
	//TCCR2B |= ((0 << CS22) | (1 << CS21) | (0 << CS20)); 	// sets prescaler at 8			 2MHz => 500ns
	//TCCR2B |= ((0 << CS22) | (1 << CS21) | (1 << CS20)); 	// sets prescaler at 32		   500kHz =>  2us
	//TCCR2B |= ((1 << CS22) | (0 << CS21) | (0 << CS20)); 	// sets prescaler at 64		   250kHz =>  4us
	//TCCR2B |= ((1 << CS22) | (0 << CS21) | (1 << CS20)); 	// sets prescaler at 128	   125kHz =>  8us
	//TCCR2B |= ((1 << CS22) | (1 << CS21) | (0 << CS20)); 	// sets prescaler at 256	   62.5kHz => 16us
	//TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));	// sets prescaler at 1024	  15,625Hz => 64us

} //=====================================================

//enum T2_CompOutMode {T2_COM_DISCONNECT=0, T2_COM_TOGGLE};
void T2_set_comA(T2_CompOutMode co_mode) {
	// set Compare Output Mode
	byte mode = 0;
	if (co_mode == T2_COM_TOGGLE) mode = 1;
	TCCR2A |= ((0 << COM2A1) | (mode << COM2A0));	// 00 - disconnected	01 - toggle

} //=====================================================

void T2_set_comB(T2_CompOutMode co_mode) {
	// set Compare Output Mode
	byte mode_bit = 0;
	if (co_mode == T2_COM_TOGGLE) mode_bit = 1;

	TCCR2A |= ((0 << COM2B1) | (mode_bit << COM2B0));	// 00 - disconnected	01 - toggle

	//TCCR2A |= ((0 << COM2A1) | (1 << COM2A0));	// 00 - disconnected	01 - toggle
	//TCCR2A |= ((0 << COM2B1) | (1 << COM2B0));	// 00 - disconnected	01 - toggle
} //=====================================================

unsigned int T2_prescale_factor(const T2_pscale prescale_selector) {

	//Serial.print(" <@Timers> prescale_factor("); Serial.print(prescale_selector); Serial.print(") = ");

	unsigned int scale = 0;
	switch (prescale_selector) {
	case T2_PSCALE_0:
		scale = 0;		// prescaler at 0		   stop
		break;
	case T2_PSCALE_1:
		scale = 1;		// prescaler at 1		   16MHz =>  62.5ns
		break;
	case T2_PSCALE_8:
		scale = 8; 		// prescaler at 8		    2MHz => 500ns
		break;
	case T2_PSCALE_32:
		scale = 32; 		// prescaler at 32		  500kHz =>  2us
		break;
	case T2_PSCALE_64:
		scale = 64; 		// prescaler at 64		  250kHz =>  4us
		break;
	case T2_PSCALE_128:
		scale = 128; 	// prescaler at 128	      125kHz =>  8us
		break;
	case T2_PSCALE_256:
		scale = 256; 	// prescaler at 256	     62.5kHz => 16us
		break;
	case T2_PSCALE_1024:
		scale = 1024;	// prescaler at 1024	15,625Hz => 64us
		break;
	default: // impossible
		scale = 0;
	}

	//Serial.print(scale); Serial.print("\t");
	//if (scale ==0) Serial.print("illegal argument value\t");
	//Serial.print("\n");

	return scale;

}

