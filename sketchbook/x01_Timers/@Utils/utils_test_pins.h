
// utils_test_pins.h

#ifndef _utils_test_pins_h
#define _utils_test_pins_h

#include "arduino.h"


//***************************************************
#define MAX_TEST_PIN 100

#if ACTIVITY_PIN == 13
const byte activity_pin = ACTIVITY_PIN;		// B5
#define SetActivityPin   		PORTB |= (1 << PORTB5)  
#define ClearActivityPin   		PORTB &= ~(1 << PORTB5) 
#define ToggleActivityPin   	PINB |= (1 << PINB5) 

#elif ACTIVITY_PIN == 12
const byte activity_pin = ACTIVITY_PIN;		// B4
#define SetActivityPin   		PORTB |= (1 << PORTB4)  
#define ClearActivityPin   		PORTB &= ~(1 << PORTB4) 
#define ToggleActivityPin   	PINB |= (1 << PINB4) 

#elif ACTIVITY_PIN == 8
const byte activity_pin = ACTIVITY_PIN;		// B0
#define SetActivityPin   		PORTB |= (1 << PORTB0)  
#define ClearActivityPin   		PORTB &= ~(1 << PORTB0)
#define ToggleActivityPin   	PIND |= (1 << PIND7) 

#elif ACTIVITY_PIN == 7
const byte activity_pin = ACTIVITY_PIN;		// D7
#define SetActivityPin   		PORTD |= (1 << PORTD7)  
#define ClearActivityPin  		PORTD &= ~(1 << PORTD7) 
#define ToggleActivityPin   	PIND |= (1 << PIND7) 

#elif ACTIVITY_PIN == 6
const byte activity_pin = ACTIVITY_PIN;		// D6
#define SetActivityPin   		PORTD |= (1 << PORTD6)  
#define ClearActivityPin  		PORTD &= ~(1 << PORTD6) 
#define ToggleActivityPin   	PIND |= (1 << PIND6) 

#elif !defined ACTIVITY_PIN
#define ACTIVITY_PIN MAX_TEST_PIN + 1
#define SetActivityPin   		;
#define ClearActivityPin  		;
#define ToggleActivityPin   	;

#elif defined ACTIVITY_PIN
#error Invalid ACTIVITY_PIN number 
#endif

//***************************************************


#if TIMING_PIN == 13
const byte timing_pin = TIMING_PIN;		// B5
#define SetTimingPin   			PORTB |= (1 << PORTB5)  
#define ClearTimingPin   		PORTB &= ~(1 << PORTB5)
#define ToggleTimingPin   		PINB |= (1 << PINB5) 


#elif TIMING_PIN == 12
const byte timing_pin = TIMING_PIN;		// B4
#define SetTimingPin   			PORTB |= (1 << PORTB4)  
#define ClearTimingPin   		PORTB &= ~(1 << PORTB4) 
#define ToggleTimingPin   		PINB |= (1 << PINB4) 

#elif TIMING_PIN == 8
const byte timing_pin = TIMING_PIN;		// B0
#define SetTimingPin   		PORTB |= (1 << PORTB0)  
#define ClearTimingPin   	PORTB &= ~(1 << PORTB0) 
#define ToggleTimingPin   		PINB |= (1 << PINB0) 


#elif TIMING_PIN == 7
const byte timing_pin = TIMING_PIN;		// D7
#define SetTimingPin   			PORTD |= (1 << PORTD7)  
#define ClearTimingPin   		PORTD &= ~(1 << PORTD7) 
#define ToggleTimingPin   		PIND |= (1 << PIND7) 

#elif TIMING_PIN == 6
const byte timing_pin = TIMING_PIN;		// D6
#define SetTimingPin   			PORTD |= (1 << PORTD6)  
#define ClearTimingPin   		PORTD &= ~(1 << PORTD6) 
#define ToggleTimingPin   		PIND |= (1 << PIND6) 

#elif !defined TIMING_PIN
#define TIMING_PIN MAX_TEST_PIN + 2
#define SetTimingPin   		; 
#define ClearTimingPin   	;
#define ToggleTimingPin   	; 

#elif defined TIMING_PIN
#error Invalid TIMING_PIN number 
#endif
//***************************************************


#if SYNC_PIN == 13
const byte sync_pin = SYNC_PIN;		// B5
#define SetSyncPin   			PORTB |= (1 << PORTB5)  
#define ClearSyncPin   			PORTB &= ~(1 << PORTB5) 
#define ToggleSyncPin   		PINB |= (1 << PINB5) 

#elif SYNC_PIN == 12
const byte sync_pin = SYNC_PIN;		// B4
#define SetSyncPin   			PORTB |= (1 << PORTB4)  
#define ClearSyncPin   			PORTB &= ~(1 << PORTB4) 
#define ToggleSyncPin   		PINB |= (1 << PINB4) 

#elif SYNC_PIN == 8
const byte sync_pin = SYNC_PIN;		// B0
#define SetSyncPin   			PORTB |= (1 << PORTB0)  
#define ClearSyncPin   			PORTB &= ~(1 << PORTB0)
#define ToggleSyncPin   		PINB |= (1 << PINB0) 

#elif SYNC_PIN == 7
const byte sync_pin = SYNC_PIN;		// D7
#define SetSyncPin   			PORTD |= (1 << PORTD7)  
#define ClearSyncPin  			PORTD &= ~(1 << PORTD7) 
#define ToggleSyncPin   		PIND |= (1 << PIND7) 

#elif SYNC_PIN == 6
const byte sync_pin = SYNC_PIN;		// D6
#define SetSyncPin   			PORTD |= (1 << PORTD6)  
#define ClearSyncPin  			PORTD &= ~(1 << PORTD6) 
#define ToggleSyncPin   		PIND |= (1 << PIND6) 

#elif !defined SYNC_PIN
#define SYNC_PIN MAX_TEST_PIN + 3
#define SetSyncPin   			; 
#define ClearSyncPin  			;
#define ToggleSyncPin   		; 

#elif defined SYNC_PIN
#error Invalid SYNC_PIN number
#endif
//***************************************************

#if PROBE_PIN == 13
const byte probe_pin = PROBE_PIN;		// B5
#define SetProbePin   			PORTB |= (1 << PORTB5)  
#define ClearProbePin   		PORTB &= ~(1 << PORTB5) 
#define ToggleProbePin   		PINB |= (1 << PINB5) 

#elif PROBE_PIN == 12
const byte probe_pin = PROBE_PIN;		// B4
#define SetProbePin   			PORTB |= (1 << PORTB4)  
#define ClearProbePin   		PORTB &= ~(1 << PORTB4) 
#define ToggleProbePin   		PINB |= (1 << PINB4 

#elif PROBE_PIN == 8
const byte probe_pin = PROBE_PIN;		// B0
#define SetProbePin   			PORTB |= (1 << PORTB0)  
#define ClearProbePin   		PORTB &= ~(1 << PORTB0)
#define ToggleProbePin   		PIND |= (1 << PIND7) 

#elif PROBE_PIN == 7
const byte probe_pin = PROBE_PIN;		// D7
#define SetProbePin   			PORTD |= (1 << PORTD7)  
#define ClearProbePin  			PORTD &= ~(1 << PORTD7) 
#define ToggleProbePin   		PIND |= (1 << PIND7) 

#elif PROBE_PIN == 6
const byte probe_pin = PROBE_PIN;		// D6
#define SetProbePin   			PORTD |= (1 << PORTD6)  
#define ClearProbePin  			PORTD &= ~(1 << PORTD6) 
#define ToggleProbePin   		PIND |= (1 << PIND6) 

#elif !defined PROBE_PIN
#define PROBE_PIN MAX_TEST_PIN + 4
#define SetProbePin   			;
#define ClearProbePin  			; 
#define ToggleProbePin   		;

#elif defined PROBE_PIN
#error Invalid PROBE_PIN number
#endif
//***************************************************

#if AUX_PIN == 13
const byte aux_pin = AUX_PIN;		// B5
#define SetAuxPin   			PORTB |= (1 << PORTB5)  
#define ClearAuxPin   			PORTB &= ~(1 << PORTB5) 
#define ToggleAuxPin   			PINB |= (1 << PINB5) 

#elif AUX_PIN == 12
const byte aux_pin = AUX_PIN;		// B4
#define SetAuxPin   			PORTB |= (1 << PORTB4)  
#define ClearAuxPin   			PORTB &= ~(1 << PORTB4) 
#define ToggleAuxPin   			PINB |= (1 << PINB4 

#elif AUX_PIN == 8
const byte aux_pin = AUX_PIN;		// B0
#define SetAuxPin   			PORTB |= (1 << PORTB0)  
#define ClearAuxPin   			PORTB &= ~(1 << PORTB0)
#define ToggleAuxPin   			PIND |= (1 << PIND7) 

#elif AUX_PIN == 7
const byte aux_pin = AUX_PIN;		// D7
#define SetAuxPin   			PORTD |= (1 << PORTD7)  
#define ClearAuxPin  			PORTD &= ~(1 << PORTD7) 
#define ToggleAuxPin   			PIND |= (1 << PIND7) 

#elif AUX_PIN == 6
const byte aux_pin = AUX_PIN;		// D6
#define SetAuxPin   			PORTD |= (1 << PORTD6)  
#define ClearAuxPin  			PORTD &= ~(1 << PORTD6) 
#define ToggleAuxPin   			PIND |= (1 << PIND6) 

#elif !defined AUX_PIN
#define AUX_PIN MAX_TEST_PIN + 5
#define SetAuxPin   		;
#define ClearAuxPin  		; 
#define ToggleAuxPin   		;

#elif defined AUX_PIN
#error Invalid AUX_PIN number
#endif

//***************************************************************************
//*** duplicate use checks ***************************************************

#if ACTIVITY_PIN==TIMING_PIN
#error Invalid ACTIVITY_PIN==TIMING_PIN number 
#endif
#if TIMING_PIN==SYNC_PIN
#error Invalid TIMING_PIN==SYNC_PIN number 
#endif
#if SYNC_PIN==PROBE_PIN
#error Invalid SYNC_PIN==PROBE_PIN number 
#endif
#if PROBE_PIN==AUX_PIN
#error Invalid PROBE_PIN==AUX_PIN number 
#endif
#if AUX_PIN==ACTIVITY_PIN
#error Invalid AUX_PIN==ACTIVITY_PIN number 
#endif

#if ACTIVITY_PIN==SYNC_PIN
#error Invalid ACTIVITY_PIN==SYNC_PIN number 
#endif
#if SYNC_PIN==AUX_PIN
#error Invalid SYNC_PIN==AUX_PIN number 
#endif
#if AUX_PIN==TIMING_PIN
#error Invalid AUX_PIN==TIMING_PIN number 
#endif
#if TIMING_PIN==PROBE_PIN
#error Invalid TIMING_PIN==PROBE_PIN number 
#endif
#if PROBE_PIN==ACTIVITY_PIN
#error Invalid PROBE_PIN==ACTIVITY_PIN number 
#endif


//*** setup functions ***************************************************

#define _showPin(m,p) \
Serial.print((m));\
if((p) < 100) Serial.println((p)); else  Serial.println("-");

#if (defined ACTIVITY_PIN) & (ACTIVITY_PIN < MAX_TEST_PIN)
#define _SetActivityMode pinMode(activity_pin, OUTPUT);\
_showPin("\tActivity: ", activity_pin)

#else 
#define _SetActivityMode
#endif

#if (defined TIMING_PIN) & (TIMING_PIN < MAX_TEST_PIN)
#define _SetTimingMode pinMode(timing_pin, OUTPUT);\
_showPin("\tTiming:\t  ", timing_pin)

#else 
#define _SetTimingMode
#endif

#if (defined SYNC_PIN) & (SYNC_PIN < MAX_TEST_PIN)
#define _SetSyncMode pinMode(sync_pin, OUTPUT);\
_showPin("\tSync:\t  ", sync_pin)

#else 
#define _SetSyncMode
#endif

#if (defined PROBE_PIN) & (PROBE_PIN < MAX_TEST_PIN)
#define _SetProbeMode pinMode(probe_pin, OUTPUT);\
_showPin("\tProbe:\t  ", probe_pin)

#else 
#define _SetProbeMode
#endif

#if (defined AUX_PIN) & (AUX_PIN < MAX_TEST_PIN)
#define _SetAuxMode pinMode(aux_pin, OUTPUT);\
_showPin("\tAux:\t  ", aux_pin)

#else 
#define _SetAuxMode
#endif

//***************************************************

#define ActivityPinName "Activity"
#define TimingPinName "Timing"
#define SyncPinName "Sync"
#define ProbePinName "Probe"
#define AuxPinName "Aux"

//***************************************************

#define SetupTestPins   \
Serial.print("\nTest pins:\n");\
_SetActivityMode  _SetTimingMode _SetSyncMode _SetProbeMode _SetAuxMode ;\
Serial.print("\n");


//***************************************************
#endif // #ifndef _UTILS_PREPROC_h
