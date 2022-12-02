
/*
* TCCR1A	7		6		5		4		3	2	   1	   0
*		COM1A1	COM1A0	COM1B1	COM1B0		-	-	WGM11	WGM10
*		   r/w	   r/w	   r/w	   r/w		r	r	  r/w	  r/w
*
*	COM1A/B/1:0 for non-PWM modes
*		00 - normal port operation, OC1A/B/ disconnected
*		01 - toggle OC1A/B/ on compare match
*		10 - clear
*		11 - set
*
*	OC1A and OC1B connect to pins D9 and D10 (should be configured as OUTPUT)
*
*	WGM13:0
*		0000 - normal
*		0100 - CTC with OCR1A
*		1100 - CTC with ICR1
*
*
* TCCR1B	7		6		5	   4		3		  2		  1		  0
*		 ICNC1	 ICES1		-	WGM13	 WGM12		CS12	CS11	CS10
*			w		w		r	   r		r		 r/w	 r/w	 r/w
*
*	CS22:0
*		000 - stop				100 - div by  256
*		001 - div by  1			101 - div by 1024
*		010 - div by  8			110 - ext on T1 pin, falling
*		011 - div by 64			111 - ext on T1 pin, rising
*
* TIMSK2	7	6		5	4	3		2		1		0
*			-	-	 ICIE1	-	-	OCIE1B	OCIE1A	 TOIE1
*			r	r		r	r	r	   r/w	   r/w	   r/w
*
*	TCNT1 - Timer/Counter Register			TCNT1[15:0]
*	OCR1A - Output Compare Register A		OCR1A[15:0]
*	OCR1B - Output Compare Register B		OCR1B[15:0]
*
*
*/

#if 0

#include "T1_setup.h"

void T1_set_wfgmode(T1_wfgmode wfg_mode) {

	// set Waveform Generation Mode
	switch (wfg_mode)
	{
	case T1_WGM_CTC:
		TCCR1B |= ((0 << WGM13) | (1 << WGM12));
		TCCR1A |= ((0 << WGM11) | (0 << WGM10));	// 0100 - CTC (4)
		break;

	case T1_WGM_NORMAL:
	default:
		TCCR1B |= ((0 << WGM13) | (0 << WGM12));
		TCCR1A |= ((0 << WGM11) | (0 << WGM10));	// 0000 - normal (default)
	}

} //=====================================================

void T1_set_intmask(byte oc_A, byte oc_B, byte ovf) {
	//set interrupts
	TIMSK1 = ((0 << ICIE1) | (oc_A << OCIE1A) | (oc_B << OCIE1B) | (ovf << TOIE1));   // set overflow and copmpares interrupts

} //=====================================================

void T1_set_prescaler(T1_pscale_id prescale_selector) {

	// clear the 3 bits first
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
		
	// set prescaler and start the counter

	switch (prescale_selector) {
	case T1_PSCALE_0:
		//TCCR1B |= ((0 << CS12) | (0 << CS11) | (0 << CS10)); 	// sets prescaler at 0			stop	// already cleared
		break;
	case T1_PSCALE_1:
		TCCR1B |= ((0 << CS12) | (0 << CS11) | (1 << CS10)); 	// sets prescaler at 1			16MHz =>  62.5ns
		break;
	case T1_PSCALE_8:
		TCCR1B |= ((0 << CS12) | (1 << CS11) | (0 << CS10)); 	// sets prescaler at 8			 2MHz => 500ns
		break;
	case T1_PSCALE_64:
		TCCR1B |= ((0 << CS12) | (1 << CS11) | (1 << CS10)); 	// sets prescaler at 64		   250kHz =>  4us
		break;
	case T1_PSCALE_256:
		TCCR1B |= ((1 << CS12) | (0 << CS11) | (0 << CS10)); 	// sets prescaler at 256	   62.5kHz => 16us
		break;
	case T1_PSCALE_1024:
		TCCR1B |= ((1 << CS12) | (0 << CS11) | (1 << CS10)); 	// sets prescaler at 1024	  15,625Hz => 64us
		break;
	//case T1_PSCALE_EXT_F:
	//	TCCR1B |= ((1 << CS12) | (1 << CS11) | (0 << CS10)); 	// external clock on T1 pin, falling edge
	//	break;
	//case T1_PSCALE_EXT_R:
	//	TCCR1B |= ((1 << CS12) | (1 << CS11) | (1 << CS10));	   // external clock on T1 pin, rising edge

	default:
		TCCR1B |= ((0 << CS12) | (1 << CS11) | (1 << CS10)); 	// sets prescaler at 64		   250kHz =>  4us

	}

} //=====================================================

void T1_stop() {
	T1_set_prescaler(T1_PSCALE_0);
}

//enum T2_CompOutMode {COM_DISCONNECT=0, COM_TOGGLE};
void T1_set_comA(T1_CompOutMode co_mode) {
	// set Compare Output Mode
	byte mode = 0;
	if (co_mode == T1_COM_TOGGLE) mode = 1;
	TCCR1A |= ((0 << COM1A1) | (mode << COM1A0));	// 00 - disconnected	01 - toggle

} //=====================================================

void T1_set_comB(T1_CompOutMode co_mode) {
	// set Compare Output Mode
	byte mode_bit = 0;
	if (co_mode == T1_COM_TOGGLE) mode_bit = 1;

	TCCR1A |= ((0 << COM1B1) | (mode_bit << COM1B0));	// 00 - disconnected	01 - toggle

	//TCCR2A |= ((0 << COM2A1) | (1 << COM2A0));	// 00 - disconnected	01 - toggle
	//TCCR2A |= ((0 << COM2B1) | (1 << COM2B0));	// 00 - disconnected	01 - toggle
} //=====================================================

#endif