#if  0

#include "T1_aux.h"

#include "..\@Utils\utils.h"


unsigned int T1_prescale_factor_old(const T1_pscale_id prescale_selector) {

	//Serial.print(" <@Timers T1> prescale_factor("); Serial.print(prescale_selector); Serial.print(") = ");

	unsigned int scale = 0;
	switch (prescale_selector) {
	case T1_PSCALE_0:
		scale = 0;		// prescaler at 0		   stop
		break;
	case T1_PSCALE_1:
		scale = 1;		// prescaler at 1		   16MHz =>  62.5ns
		break;
	case T1_PSCALE_8:
		scale = 8; 		// prescaler at 8		    2MHz => 500ns
		break;
	case T1_PSCALE_64:
		scale = 64; 		// prescaler at 64		  250kHz =>  4us
		break;
	case T1_PSCALE_256:
		scale = 256; 	// prescaler at 256	     62.5kHz => 16us
		break;
	case T1_PSCALE_1024:
		scale = 1024;	// prescaler at 1024	15,625Hz => 64us
		break;
	default: // impossible
		scale = 0;
	}

	//Serial.print(scale); Serial.print("\t");
	//if (scale == 0) Serial.print("illegal argument value\t");
	//Serial.print("\n");

	return scale;

}

unsigned int T1_prescale_factor_new(const T1_pscale_id prescale_selector) {

	return T1_pscale_div[prescale_selector];

}



void PrintSeparator() { // divider
	const byte N = 8;
	Serial.print("\t-");
	for (int i = N - 1; i >= 0; i--) {
		Serial.print("------");
	}
	Serial.print("\n");
}

void PrintOneRegister(byte v, char* reg_name) {

	Serial.print(reg_name);	Serial.print("\t");

	//	void printReg(uint8_t v)
	{
		const byte N = 8;
		char* f_pad = "  ";
		char* e_pad = " | ";
		byte flen = strlen(f_pad) + strlen(e_pad) + 1;

		Serial.print("|");
		for (int i = N - 1; i >= 0; i--) {
			Serial.print("  ");
			if (bitRead(v, i))		Serial.print("1");
			else Serial.print(" ");

			Serial.print("  |");
		}

	}
	Serial.print("\n");
	PrintSeparator();

}


char* Timer1_WGMode(char* wgmode, byte wgm_id) {

	switch (wgm_id) {
	case 0:		strcpy(wgmode, "Normal");								break;
	case 1:		strcpy(wgmode, "PWM, phase correct, 8-bit");			break;
	case 2:		strcpy(wgmode, "PWM, phase correct, 9-bit");			break;
	case 3:		strcpy(wgmode, "PWM, phase correct, 10-bit");			break;
	case 4:		strcpy(wgmode, "CTC | OCR1A");							break;
	case 5:		strcpy(wgmode, "Fast PWM, 8-bit");						break;
	case 6:		strcpy(wgmode, "Fast PWM, 9-bit");						break;
	case 7:		strcpy(wgmode, "Fast PWM, 10-bit");						break;
	case 8:		strcpy(wgmode, "PWM, phase & freq correct | ICR1");		break;
	case 9:		strcpy(wgmode, "PWM, phase & freq correct | OCR1A");	break;
	case 10:	strcpy(wgmode, "PWM, phase correct | ICR1");			break;
	case 11:	strcpy(wgmode, "PWM, phase correct | OCR1A");			break;
	case 12:	strcpy(wgmode, "CTC | ICR1");							break;
	case 13:	strcpy(wgmode, "(Reserved)");							break;
	case 14:	strcpy(wgmode, "Fast PWM | ICR1");						break;
	case 15:	strcpy(wgmode, "Fast PWM | OCR1A");						break;
	default:	strcpy(wgmode, "invalid");
	}

	return wgmode;
}

char* Timer1_CSMode(char* csmode, byte cs_id) {
	switch (cs_id) {
	case 0:	strcpy(csmode, "stopped");				break;
	case 1:	strcpy(csmode, "1/1");				break;
	case 2:	strcpy(csmode, "1/8");				break;
	case 3:	strcpy(csmode, "1/64");				break;
	case 4:	strcpy(csmode, "1/256");				break;
	case 5:	strcpy(csmode, "1/1024");				break;
	case 6:	strcpy(csmode, "external, falling");				break;
	case 7:	strcpy(csmode, "external, rising");				break;
	default:	strcpy(csmode, "invalid");
	}
	return csmode;
}

char* Timer1_COMode(char* comode, byte co_id) {
	switch (co_id) {
	case 0:	strcpy(comode, "Disconnected");			break;
	case 1:	strcpy(comode, "Toggle");				break;
	case 2:	strcpy(comode, "Clear");				break;
	case 3:	strcpy(comode, "Set");				break;
	default:	strcpy(comode, "invalid");
	}
	return comode;
}

char* Timer1_IntMode(char* intmode, byte int_id) {
	switch (int_id) {
	case 0:	strcpy(intmode, "Disabled");			break;
	case 1:	strcpy(intmode, "Enabled");				break;
	default:	strcpy(intmode, "invalid");
	}
	return intmode;
}

byte Timer1_WG_ID() {
	byte wgm13, wgm12, wgm11, wgm10, wgm_id = 0;
	wgm13 = (TCCR1B >> WGM13) & 0x1;
	wgm12 = (TCCR1B >> WGM12) & 0x1;
	wgm11 = (TCCR1A >> WGM11) & 0x1;
	wgm10 = (TCCR1A >> WGM10) & 0x1;
	wgm_id = (wgm13 << 3) | (wgm12 << 2) | (wgm11 << 1) | (wgm10 << 0);
	return wgm_id;
}

byte Timer1_CS_ID() {
	byte cs12, cs11, cs10, cs_id = 0;
	cs12 = (TCCR1B >> CS12) & 0x1;
	cs11 = (TCCR1B >> CS11) & 0x1;
	cs10 = (TCCR1B >> CS10) & 0x1;
	cs_id = (cs12 << 2) | (cs11 << 1) | (cs10 << 0);
	return cs_id;
}

byte Timer1_COA_ID() {
	byte com1a1, com1a0, coa_id = 0;
	com1a1 = (TCCR1A >> COM1A1) & 0x1;
	com1a0 = (TCCR1A >> COM1A0) & 0x1;
	coa_id = (com1a1 << 1) | (com1a0 << 0);
	return coa_id;
}

byte Timer1_COB_ID() {
	byte com1b1, com1b0, cob_id = 0;
	com1b1 = (TCCR1A >> COM1B1) & 0x1;
	com1b0 = (TCCR1A >> COM1B0) & 0x1;
	cob_id = (com1b1 << 1) | (com1b0 << 0);
	return cob_id;
}

void AnalyzeStatusT1() {

	// WG mode
	{
		byte wgm_id = Timer1_WG_ID();						// extract mode id from ctrl register(s)
		char wgmode[35]; Timer1_WGMode(wgmode, wgm_id);		// mode description for id

		Serial.print("\n\tWGM13:10  \t");
		Serial.print(wgm_id); Serial.print("\t"); Serial.print(wgmode); Serial.print("\n");
	}

	// Prescaler
	{
		byte cs_id = Timer1_CS_ID();						// extract prescaler id from ctrl register(s)
		char csmode[20];	Timer1_CSMode(csmode, cs_id);	// mode description for id

		Serial.print("\n\tCS12:10   \t");
		Serial.print(cs_id); Serial.print("\t"); Serial.print(csmode); Serial.print("\n");
	}

	// Output Comparators
	{
		byte co_id; char comode[20];
		co_id = Timer1_COA_ID();						// extract CO id from ctrl register(s)
		Timer1_COMode(comode, co_id);	// mode description for id

		Serial.print("\n\tCOM1A1:0   \t");
		Serial.print(co_id); Serial.print("\t"); Serial.print(comode); Serial.print("\n");

		co_id = Timer1_COB_ID();						// extract CO id from ctrl register(s)
		Timer1_COMode(comode, co_id);	// mode description for id

		Serial.print("\tCOM1B1:0   \t");
		Serial.print(co_id); Serial.print("\t"); Serial.print(comode); Serial.print("\n");
	}

	// Interrupts
	{
		byte intr_id; char intmode[10];

		intr_id = (TIMSK1 >> TOIE1) & 0x1;	// extract id from ctrl register(s)
		Timer1_IntMode(intmode, intr_id);	// mode description for id

		Serial.print("\n\tTOIE1   \t");
		Serial.print(intr_id); Serial.print("\t"); Serial.print(intmode); Serial.print("\n");

		intr_id = (TIMSK1 >> OCIE1A) & 0x1;	// extract id from ctrl register(s)
		Timer1_IntMode(intmode, intr_id);	// mode description for id

		Serial.print("\n\tOCIE1A   \t");
		Serial.print(intr_id); Serial.print("\t"); Serial.print(intmode); Serial.print("\n");

		intr_id = (TIMSK1 >> OCIE1B) & 0x1;	// extract id from ctrl register(s)
		Timer1_IntMode(intmode, intr_id);	// mode description for id

		Serial.print("\tOCIE1B   \t");
		Serial.print(intr_id); Serial.print("\t"); Serial.print(intmode); Serial.print("\n");
		Serial.flush();
	}

	// 16 bit registers
	{
		Serial.print("\n");
		Serial.print("\tOCR1A   \t");
		Serial.print(OCR1A);  Serial.print("\n");


		Serial.print("\tOCR1B   \t");
		Serial.print(OCR1B);  Serial.print("\n");

		Serial.print("\tICR1    \t");
		Serial.print(ICR1);  Serial.print("\n");

	}


}

void Show16bitRegisters_T1(char* msg) {

	// message/identifier
	Serial.print("\n  ");
	Serial.println(msg);


	// 16 bit registers
	Serial.print("\n");
	Serial.print("\tOCR1A   \t");
	Serial.print(OCR1A);  Serial.print("\n");


	Serial.print("\tOCR1B   \t");
	Serial.print(OCR1B);  Serial.print("\n");

	Serial.print("\tICR1    \t");
	Serial.print(ICR1);  Serial.print("\n");

}

void Show16bitRegisters_T1() {
	Show16bitRegisters_T1("");
}


void ShowConfig_T1() {
	ShowConfig_T1("");
}

void ShowConfig_T1(char* msg) {

	const byte N = 8;

	// message/identifier
	Serial.print("\n  ");
	Serial.println(msg);

	//header
	{
		Serial.print("\t ");
		for (int i = N - 1; i >= 0; i--) {
			Serial.print("  "); Serial.print(i);
			Serial.print("   ");
		}
		Serial.print("\n");

		Serial.print("\t=");
		for (int i = N - 1; i >= 0; i--) {
			Serial.print("======");
		}
		Serial.print("\n");
	}

	PrintOneRegister(TIMSK1, "TIMSK1");
	PrintOneRegister(TIFR1, "TIFR1");
	PrintOneRegister(TCCR1A, "TCCR1A");
	PrintOneRegister(TCCR1B, "TCCR1B");
	//PrintOneRegister(TCCR1C, "TCCR1C");

	AnalyzeStatusT1();

	Serial.flush();

}


void ShowScaleFactors() {
	dpr("<ListScaleFactors>"); dnl;
	for (byte i = 0; i < T1_PSCALE_N; i++) {
		T1_pscale_id s = T1_pscale_id(i);
		if (i == 0) {
			dtb; dpr("i"); dtb; dpr("s"); dtb; dpr("ps factor"); dnl;
			for (byte j = 0; j < 3; j++) {	dtb; dpr("======");} dnl;
		}
		{
			dtb; dpr(i); dtb; dpr(s); dtb; dpr(T1_prescale_factor(s)); dnl;
		}
	}
	dnl;
}

#endif