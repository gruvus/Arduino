/*
 Created:	8/28/2022 12:31:59 AM
   use analog output on Due to produce some wave forms; no explicit timing for sample freq (just prog loop)
   wave_gen study created under Arduino IDE ported to VS, split in multiple source files

   Study goal 1: execise analog output on Due
   Study goal 2: split project in multiple files
   
   */

#include "wave_gen_math.h"

const int LED_PIN = 40; // LED_BUILTIN;
int DAC_PIN = DAC0; // analog out

const byte ADC_BITS = 12; // ADC resolution, max 12
const byte DAC_BITS = 12; // DAC resolution max 12; analog output range is reduced

const int TEST = 0, SQUARE = 1, BURST = 2, TRIANGLE = 3, SINE = 4, RANDOM = 5;

//====== Parameters ======
int wave_form = TRIANGLE;

const float REL_LO = 0, REL_HI = 1; // output range limits relative to DAC range
//const float REL_LO = 0.25, REL_HI = 0.75;

int OUT_STEPS = 5;  // 0 = max

//const bool VERBOSE = false, BLINK = true;
#ifdef _VMDEBUG
const bool VERBOSE = true, BLINK = true;
#else
const bool VERBOSE = true, BLINK = true;
#endif // VM_DEBUG


//global variables
int DAC_LO, DAC_HI, DAC_MAX, OUT_MAX; // initialized in setup()
const int DAC_MIN = 0, OUT_MIN = 0; //  always 0; just for expresivity in mapping ranges


int values[4096]; // half period samples; symetric waveforms (ascending-descending)


//===============================
void setup() {
	pinMode(LED_PIN, OUTPUT);
	//  pinMode(DAC_PIN, OUTPUT); // not necessary
	Serial.begin(115200);

	analogReadResolution(ADC_BITS);
	analogWriteResolution(DAC_BITS);

	// calculate ranges
	DAC_MAX = pow(2, DAC_BITS) - 1;
	DAC_LO = DAC_MAX * REL_LO;
	DAC_HI = DAC_MAX * REL_HI;
	int dac_steps = DAC_HI - DAC_LO + 1;

	if ((OUT_STEPS < 1) || (OUT_STEPS > dac_steps)) OUT_STEPS = dac_steps;
	OUT_MAX = OUT_STEPS - 1;


	Serial.print("\n\n\n\n\n**********  Analog waveform ganerator  **********\n\n");
	Serial.print("Analog Read resolution: \t");   Serial.print(ADC_BITS); Serial.println(" bits");
	Serial.print("Analog Write resolution: \t");  Serial.print(DAC_BITS); Serial.println(" bits");

	Serial.print("DAC full range:     ");
	Serial.print(DAC_MIN);    Serial.print("\t\t");
	Serial.print(DAC_MAX);    Serial.print("\n");

	Serial.print("DAC used range:     ");
	Serial.print(DAC_LO);    Serial.print("\t\t");
	Serial.print(DAC_HI);    Serial.print("\n");

	Serial.print("Relative range:     ");
	Serial.print(REL_LO);    Serial.print("\t");
	Serial.print(REL_HI);    Serial.print("\n");

	Serial.print("Sample count range: ");
	Serial.print(OUT_MIN);    Serial.print("\t\t");
	Serial.print(OUT_MAX);    Serial.print("\n");
	Serial.print("\n");

	Serial.print("Wave form: "); print_wave_name(); Serial.print("\n\n");

} //void setup()
