
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
* TIMSKn	7	6		5	4	3		2		1		0
*			-	-	 ICIEn	-	-	OCIEnB	OCIEnA	 TOIEn
*			r	r		r	r	r	   r/w	   r/w	   r/w
*
*	TCNTn  - Timer/Counter Register			TCNTn[15:0]
*	 OCRnA - Output Compare Register A		OCRnA[15:0]
*	 OCRnB - Output Compare Register B		OCRnB[15:0]
*	 OCRnC - Output Compare Register C		OCRnC[15:0]
*	 ICRn  - Input Capture Register			 ICRn[15:0]
*
*/



//#include "GenT16.h"

#include "T_OneShot_16bit.h"






/*

// aux status reporting function for 16bit counter
// returns text description for wgm id  
// wgm_id could be enum
char* genT16_WGMode(char* wgmode, const byte wgm_id) {

	switch (wgm_id) {
	case 0:		strcpy(wgmode, "Normal");								break;
	case 1:		strcpy(wgmode, "PWM, phase correct, 8-bit");			break;
	case 2:		strcpy(wgmode, "PWM, phase correct, 9-bit");			break;
	case 3:		strcpy(wgmode, "PWM, phase correct, 10-bit");			break;
	case 4:		strcpy(wgmode, "CTC | OCRnA");							break;
	case 5:		strcpy(wgmode, "Fast PWM, 8-bit");						break;
	case 6:		strcpy(wgmode, "Fast PWM, 9-bit");						break;
	case 7:		strcpy(wgmode, "Fast PWM, 10-bit");						break;
	case 8:		strcpy(wgmode, "PWM, phase & freq correct | ICRn");		break;
	case 9:		strcpy(wgmode, "PWM, phase & freq correct | OCRnA");	break;
	case 10:	strcpy(wgmode, "PWM, phase correct | ICRn");			break;
	case 11:	strcpy(wgmode, "PWM, phase correct | OCRnA");			break;
	case 12:	strcpy(wgmode, "CTC | ICRn");							break;
	case 13:	strcpy(wgmode, "(Reserved)");							break;
	case 14:	strcpy(wgmode, "Fast PWM | ICRn");						break;
	case 15:	strcpy(wgmode, "Fast PWM | OCRnA");						break;
	default:	strcpy(wgmode, "invalid");
	}

	return wgmode;
}

*/

