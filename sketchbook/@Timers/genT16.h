// genT16.h
// hw setup functions; hw timer instance specifc
#pragma once

#include "arduino.h"

//#define HWTIMER 2 // for test while editing ; shoul be set by the including cpp unit

#if (defined(ARDUINO_AVR_UNO)) && (HWTIMER > 1)
#error Only Timer1 supported on UNO
#endif 

#if HWTIMER == 1
#define TCNTn TCNT1
#define OCRnA OCR1A
#define OCRnB OCR1B
#define ICRn  ICR1

#define TCCRnA TCCR1A

#define COMnA0 COM1A0
#define COMnA1 COM1A1
#define COMnB0 COM1B0
#define COMnB1 COM1B1

#define  WGMn0 WGM10
#define  WGMn1 WGM11
#define  WGMn2 WGM12
#define  WGMn3 WGM13

#define TCCRnB TCCR1B

#define  CSn0 CS10
#define  CSn1 CS11
#define  CSn2 CS12

#define TIMSKn TIMSK1

#define ICIEn ICIE1
#define OCIEnA OCIE1A
#define OCIEnB OCIE1B
#define TOIEn TOIE1

#define TIMERn_OVF_vect TIMER1_OVF_vect
#define TIMERn_COMPA_vect TIMER1_COMPA_vect
#define TIMERn_COMPB_vect TIMER1_COMPB_vect

#ifdef OCR1C
#define OCRnC OCR1C
#define COMnC0 COM1C0
#define COMnC1 COM1C1
#define TIMERn_COMPC_vect TIMER1_COMPC_vect
#endif // 

#endif
#if HWTIMER == 3

#define TCNTn TCNT3
#define OCRnA OCR3A
#define OCRnB OCR3B
#define OCRnC OCR3C
#define ICRn  ICR3

#define TCCRnA TCCR3A

#define COMnA0 COM3A0
#define COMnA1 COM3A1
#define COMnB0 COM3B0
#define COMnB1 COM3B1
#define COMnC0 COM3C0
#define COMnC1 COM3C1

#define  WGMn0 WGM30
#define  WGMn1 WGM31
#define  WGMn2 WGM32
#define  WGMn3 WGM33

#define TCCRnB TCCR3B

#define  CSn0 CS30
#define  CSn1 CS31
#define  CSn2 CS32

#define TIMSKn TIMSK3

#define ICIEn ICIE3
#define OCIEnA OCIE3A
#define OCIEnB OCIE3B
#define TOIEn TOIE3

#define TIMERn_OVF_vect TIMER3_OVF_vect
#define TIMERn_COMPA_vect TIMER3_COMPA_vect
#define TIMERn_COMPB_vect TIMER3_COMPB_vect
#define TIMERn_COMPC_vect TIMER3_COMPC_vect

#endif
#if HWTIMER == 4
#define TCNTn TCNT4
#define OCRnA OCR4A
#define OCRnB OCR4B
#define OCRnC OCR4C
#define ICRn  ICR4

#define TCCRnA TCCR4A

#define COMnA0 COM4A0
#define COMnA1 COM4A1
#define COMnB0 COM4B0
#define COMnB1 COM4B1
#define COMnC0 COM4C0
#define COMnC1 COM4C1

#define  WGMn0 WGM40
#define  WGMn1 WGM41
#define  WGMn2 WGM42
#define  WGMn3 WGM43

#define TCCRnB TCCR4B

#define  CSn0 CS40
#define  CSn1 CS41
#define  CSn2 CS42

#define TIMSKn TIMSK4

#define ICIEn ICIE4
#define OCIEnA OCIE4A
#define OCIEnB OCIE4B
#define TOIEn TOIE4

#define TIMERn_OVF_vect TIMER4_OVF_vect
#define TIMERn_COMPA_vect TIMER4_COMPA_vect
#define TIMERn_COMPB_vect TIMER4_COMPB_vect
#define TIMERn_COMPC_vect TIMER4_COMPC_vect

#endif
#if HWTIMER == 5

#define TCNTn TCNT5
#define OCRnA OCR5A
#define OCRnB OCR5B
#define OCRnC OCR5C
#define ICRn  ICR5

#define TCCRnA TCCR5A

#define COMnA0 COM5A0
#define COMnA1 COM5A1
#define COMnB0 COM5B0
#define COMnB1 COM5B1
#define COMnC0 COM5C0
#define COMnC1 COM5C1

#define  WGMn0 WGM50
#define  WGMn1 WGM51
#define  WGMn2 WGM52
#define  WGMn3 WGM53

#define TCCRnB TCCR5B

#define  CSn0 CS50
#define  CSn1 CS51
#define  CSn2 CS52

#define TIMSKn TIMSK5

#define ICIEn ICIE5
#define OCIEnA OCIE5A
#define OCIEnB OCIE5B
#define TOIEn TOIE5

#define TIMERn_OVF_vect TIMER5_OVF_vect
#define TIMERn_COMPA_vect TIMER5_COMPA_vect
#define TIMERn_COMPB_vect TIMER5_COMPB_vect
#define TIMERn_COMPC_vect TIMER5_COMPC_vect

#endif

#if HWTIMER == 2		// 8bit timer
#define TCNTn TCNT2
#define OCRnA OCR2A
#define OCRnB OCR2B
//#define ICRn  ICR2

#define TCCRnA TCCR2A

#define COMnA0 COM2A0
#define COMnA1 COM2A1
#define COMnB0 COM2B0
#define COMnB1 COM2B1

#define  WGMn0 WGM20
#define  WGMn1 WGM21
#define  WGMn2 WGM22
//#define  WGMn3 WGM23

#define TCCRnB TCCR2B

#define  CSn0 CS20
#define  CSn1 CS21
#define  CSn2 CS22

#define TIMSKn TIMSK2

//#define ICIEn ICIE2
#define OCIEnA OCIE2A
#define OCIEnB OCIE2B
#define TOIEn TOIE2

#define TIMERn_OVF_vect TIMER2_OVF_vect
#define TIMERn_COMPA_vect TIMER2_COMPA_vect
#define TIMERn_COMPB_vect TIMER2_COMPB_vect

#ifdef OCR2C
#define OCRnC OCR1C
#define COMnC0 COM1C0
#define COMnC1 COM1C1
#define TIMERn_COMPC_vect TIMER1_COMPC_vect
#endif // 

#endif


// generic setup functions based on defines set by the including unit

static void ClearControlRegisters_16() {
	TCCRnA = 0;		TCCRnB = 0;		TIMSKn = 0;
	TCNTn = 1024;	// test only -> remove
}

static void ClearControlRegisters_8() {
	TCCRnA = 0;		TCCRnB = 0;		TIMSKn = 0;
	TCNTn = 128;	// test only -> remove
}

static bool SetWFGmode_16(const byte wfg_mode_id) {
	// set Waveform Generation Mode
	
	// clear the bits first
	TCCRnB &= ~((1 << WGMn3) | (1 << WGMn2));
	TCCRnA &= ~((1 << WGMn1) | (1 << WGMn0));	// 000 - normal (default)

	switch (wfg_mode_id) {
	case 0:		  //	"Normal"
		// 0000 - normal (default)
		return true;

	case 1:		break;  //	"PWM, phase correct, 8-bit"
	case 2:		break;  //	"PWM, phase correct, 9-bit"
	case 3:		break;  //	"PWM, phase correct, 10-bit"

	case 4:		 //	"CTC | OCRnA"	 0100 = 4
		TCCRnB |= ((0 << WGMn3) | (1 << WGMn2));
		TCCRnB |= ((0 << WGMn1) | (0 << WGMn0));
		return true;

	case 5:		break;  //	"Fast PWM, 8-bit"
	case 6:		break;  //	"Fast PWM, 9-bit"
	case 7:		break;  //	"Fast PWM, 10-bit"
	case 8:		break;  //	"PWM, phase & freq correct | ICRn"
	case 9:		break;  //	"PWM, phase & freq correct | OCRnA"
	case 10:	break;  //	"PWM, phase correct | ICRn"
	case 11:	break;  //	"PWM, phase correct | OCRnA"

	case 12:	//	"CTC | ICRn"  1100 = 12
		TCCRnB |= ((1 << WGMn3) | (1 << WGMn2));
		TCCRnB |= ((0 << WGMn1) | (0 << WGMn0));
		return true;

	case 13:	break;  //	"Reserved"
	case 14:	break;  //	"Fast PWM | ICRn"
	case 15:	break;  //	"Fast PWM | OCRnA"

	default:	break;  //	invalid
	}

	// not supported 
	return false;

}; //=====================================================

static bool SetWFGmode_8(const byte wfg_mode_id) {
	// set Waveform Generation Mode
	
	// clear the bits first
	TCCRnB &= ~(1 << WGMn2);
	TCCRnA &= ~((0 << WGMn1) | (0 << WGMn0));	// 000 - normal (default)


	switch (wfg_mode_id) {
	case 0:		  //	"Normal"
		// 000 - normal (default)
		return true;

	case 1:		break;  //	"PWM, phase correct, 0xFF"

	case 2:				//	"CTC | OCRA"	 010 = 2
		TCCRnB |= (1 << WGMn2);
		TCCRnB |= ((0 << WGMn1) | (0 << WGMn0));
		return true;

	case 3:		break;  //	"Fast PWM, 0xFF"
	case 4:		break;  //	"Reserved"
	case 5:		break;  //	"PWM, phase correct | OCRA"
	case 6:		break;  //	"Reserved"
	case 7:		break;  //	"Fast PWM | OCRnA"

	default:	break;  //	invalid
	}

	// not supported 
	return false;

}; //=====================================================

static void SetIntMask_16(byte ovf,  byte oc_A,  byte oc_B , byte oc_C) {
	//set interrupts

	TIMSKn = ((0 << ICIEn) | (oc_A << OCIEnA) | (oc_B << OCIEnB) | (ovf << TOIEn));


}; //=====================================================

static void SetIntMask_8(byte ovf, byte oc_A, byte oc_B, byte oc_C) {
	//set interrupts

	TIMSKn = ((oc_A << OCIEnA) | (oc_B << OCIEnB) | (ovf << TOIEn));


}; //=====================================================

static void SetPrescaler_16(const byte prescale_id) {

	// clear the bits first
	TCCRnB &= ~((1 << CSn2) | (1 << CSn1) | (1 << CSn0));

	// set prescaler and start the counter

	switch (prescale_id) {
	case 0:
		//TCCR1B |= ((0 << CSn2) | (0 << CSn1) | (0 << CSn0)); 	// sets prescaler at 0			stop	// already cleared
		break;
	case 1:
		TCCRnB |= ((0 << CSn2) | (0 << CSn1) | (1 << CSn0)); 	// sets prescaler at 1			16MHz =>  62.5ns
		break;
	case 2:
		TCCRnB |= ((0 << CSn2) | (1 << CSn1) | (0 << CSn0)); 	// sets prescaler at 8			 2MHz => 500ns
		break;
	case 3:
		TCCRnB |= ((0 << CSn2) | (1 << CSn1) | (1 << CSn0)); 	// sets prescaler at 64		   250kHz =>  4us
		break;
	case 4:
		TCCRnB |= ((1 << CSn2) | (0 << CSn1) | (0 << CSn0)); 	// sets prescaler at 256	   62.5kHz => 16us
		break;
	case 5:
		TCCRnB |= ((1 << CSn2) | (0 << CSn1) | (1 << CSn0)); 	// sets prescaler at 1024	  15,625Hz => 64us
		break;

	default: // invalid
		TCCRnB |= ((0 << CSn2) | (1 << CSn1) | (1 << CSn0));

	}

}; //=====================================================

static void SetPrescaler_8(const byte prescale_id) {

	// clear the bits first
	TCCRnB &= ~((1 << CSn2) | (1 << CSn1) | (1 << CSn0));

	// set prescaler and start the counter

	switch (prescale_id) {
	case 0:
		//TCCR1B |= ((0 << CSn2) | (0 << CSn1) | (0 << CSn0)); 	// sets prescaler at 0			stop	// already cleared
		break;
	case 1:
		TCCRnB |= ((0 << CSn2) | (0 << CSn1) | (1 << CSn0)); 	// sets prescaler at 1
		break;
	case 2:
		TCCRnB |= ((0 << CSn2) | (1 << CSn1) | (0 << CSn0)); 	// sets prescaler at 8
		break;
	case 3:
		TCCRnB |= ((0 << CSn2) | (1 << CSn1) | (1 << CSn0)); 	// sets prescaler at 32
		break;
	case 4:
		TCCRnB |= ((1 << CSn2) | (0 << CSn1) | (0 << CSn0)); 	// sets prescaler at 64
		break;
	case 5:
		TCCRnB |= ((1 << CSn2) | (0 << CSn1) | (1 << CSn0)); 	// sets prescaler at 128
		break;
	case 6:
		TCCRnB |= ((1 << CSn2) | (1 << CSn1) | (0 << CSn0)); 	// sets prescaler at 256
		break;
	case 7:
		TCCRnB |= ((1 << CSn2) | (1 << CSn1) | (1 << CSn0)); 	// sets prescaler at 1024
		break;

	default: // invalid
		TCCRnB |= ((1 << CSn2) | (0 << CSn1) | (0 << CSn0));	// sets prescaler at 64

	}

}; //=====================================================

static void SetCompA_16(const byte comp_mode_id) {
	// set Compare Output Mode

	switch (comp_mode_id) {
	case 1:
		TCCRnA |= ((0 << COMnA1) | (1 << COMnA0));	//	01 - toggle
		break;
	case 2:
		TCCRnA |= ((1 << COMnA1) | (0 << COMnA0));	//	10 - 
		break;
	case 3:
		TCCRnA |= ((1 << COMnA1) | (1 << COMnA0));	//	11 - 
		break;
	case 0:
	default:
		TCCRnA |= ((0 << COMnA1) | (0 << COMnA0));	//	00 - disconnect
	}
}

static void SetCompB_16(const byte comp_mode_id) {
	// set Compare Output Mode

	switch (comp_mode_id) {
	case 1:
		TCCRnA |= ((0 << COMnB1) | (1 << COMnB0));	//	01 - toggle
		break;
	case 2:
		TCCRnA |= ((1 << COMnB1) | (0 << COMnB0));	//	10 - 
		break;
	case 3:
		TCCRnA |= ((1 << COMnB1) | (1 << COMnB0));	//	11 - 
		break;
	case 0:
	default:
		TCCRnA |= ((0 << COMnB1) | (0 << COMnB0));	//	00 - disconnect
	}
}

static void SetCompC_16(const byte comp_mode_id) {
#ifdef OCRnC
	// set Compare Output Mode

	switch (comp_mode_id) {
	case 1:
		TCCRnA |= ((0 << COMnC1) | (1 << COMnC0));	//	01 - toggle
		break;
	case 2:
		TCCRnA |= ((1 << COMnC1) | (0 << COMnC0));	//	10 - 
		break;
	case 3:
		TCCRnA |= ((1 << COMnC1) | (1 << COMnC0));	//	11 - 
		break;
	case 0:
	default:
		TCCRnA |= ((0 << COMnC1) | (0 << COMnC0));	//	00 - disconnect
	}
#endif
}

// aux functions

static void setOCRegs_16( uint16_t Aval,  uint16_t Bval,  uint16_t Cval,  uint16_t Dval) 
{
	OCRnA = Aval; OCRnB = Bval; ICRn = Dval;

#ifdef OCRnC
	OCRnC = Cval;
#endif

}

static void showOCRegs_16( byte tag) {

	dpr("<showOCR> "); dpr(tag); dnl;

	uint16_t regval = TCNTn;

	dpr("  TCNTn at [");	dprc(uint16_t(&TCNTn), HEX); 	dpr("]");
	dtb; dprc(regval, HEX);  dtb; dpr(regval); dnl;

	regval = ICRn;
	dpr("   ICRn at [");	dprc(uint16_t(&ICRn), HEX); 	dpr("]");
	dtb; dprc(regval, HEX);  dtb; dpr(regval); dnl;

	regval = OCRnA;
	dpr("  OCRnA at [");	dprc(uint16_t(&OCRnA), HEX); 	dpr("]");
	dtb; dprc(regval, HEX);  dtb; dpr(regval); dnl;

	regval = OCRnB;
	dpr("  OCRnB at [");	dprc(uint16_t(&OCRnB), HEX); 	dpr("]");
	dtb; dprc(regval, HEX);  dtb; dpr(regval); dnl;

#ifdef OCRnC
	regval = OCRnC;
	dpr("  OCRnC at [");	dprc(uint16_t(&OCRnC), HEX); 	dpr("]");
	dtb; dprc(regval, HEX);  dtb; dpr(regval); dnl;
	dnl;
#endif

	dflush;
};
