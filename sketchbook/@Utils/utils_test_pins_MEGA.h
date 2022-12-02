#pragma once


// MEGA


#if ACTIVITY_PIN == 13
const byte activity_pin = ACTIVITY_PIN;		// B7
#define SetActivityPin   		PORTB |= (1 << PORTB7)  
#define ClearActivityPin   		PORTB &= ~(1 << PORTB7) 
#define ToggleActivityPin   	PINB = (1 << PINB7) 

#elif ACTIVITY_PIN == 12
const byte activity_pin = ACTIVITY_PIN;		// B6
#define SetActivityPin   		PORTB |= (1 << PORTB6)  
#define ClearActivityPin   		PORTB &= ~(1 << PORTB6) 
#define ToggleActivityPin   	PINB = (1 << PINB6) 

#elif ACTIVITY_PIN == 8
const byte activity_pin = ACTIVITY_PIN;		// H5
#define SetActivityPin   		PORTH |= (1 << PORTH5)  
#define ClearActivityPin   		PORTH &= ~(1 << PORTH5)
#define ToggleActivityPin   	PINH = (1 << PINH5) 

#elif ACTIVITY_PIN == 7
const byte activity_pin = ACTIVITY_PIN;		// H4
#define SetActivityPin   		PORTH |= (1 << PORTH4)  
#define ClearActivityPin  		PORTH &= ~(1 << PORTH4) 
#define ToggleActivityPin   	PINH = (1 << PINH4) 

#elif ACTIVITY_PIN == 6
const byte activity_pin = ACTIVITY_PIN;		// H3
#define SetActivityPin   		PORTH |= (1 << PORTH3)  
#define ClearActivityPin  		PORTH &= ~(1 << PORTH3) 
#define ToggleActivityPin   	PINH = (1 << PINH3) 

#elif !defined ACTIVITY_PIN
#define ACTIVITY_PIN MAX_TEST_PIN + 1
#define SetActivityPin   		
#define ClearActivityPin  		
#define ToggleActivityPin   	

#elif defined ACTIVITY_PIN
#error Invalid ACTIVITY_PIN number 
#endif

//***************************************************


#if TIMING_PIN == 13
const byte timing_pin = TIMING_PIN;		// B7
#define SetTimingPin   			PORTB |= (1 << PORTB7)  
#define ClearTimingPin   		PORTB &= ~(1 << PORTB7)
#define ToggleTimingPin   		PINB = (1 << PINB7) 


#elif TIMING_PIN == 12
const byte timing_pin = TIMING_PIN;		// B6
#define SetTimingPin   			PORTB |= (1 << PORTB6)  
#define ClearTimingPin   		PORTB &= ~(1 << PORTB6) 
#define ToggleTimingPin   		PINB = (1 << PINB6) 

#elif TIMING_PIN == 8
const byte timing_pin = TIMING_PIN;		// H5
#define SetTimingPin   			PORTH |= (1 << PORTH5)  
#define ClearTimingPin   		PORTH &= ~(1 << PORTH5) 
#define ToggleTimingPin   		PINH = (1 << PINH5) 


#elif TIMING_PIN == 7
const byte timing_pin = TIMING_PIN;		// H4
#define SetTimingPin   			PORTH |= (1 << PORTH4)  
#define ClearTimingPin   		PORTH &= ~(1 << PORTH4) 
#define ToggleTimingPin   		PINH = (1 << PINH4) 

#elif TIMING_PIN == 6
const byte timing_pin = TIMING_PIN;		// H3
#define SetTimingPin   			PORTH |= (1 << PORTH3)  
#define ClearTimingPin   		PORTH &= ~(1 << PORTH3) 
#define ToggleTimingPin   		PINH = (1 << PINH3) 

#elif !defined TIMING_PIN
#define TIMING_PIN MAX_TEST_PIN + 2
#define SetTimingPin   		 
#define ClearTimingPin   	
#define ToggleTimingPin   	 

#elif defined TIMING_PIN
#error Invalid TIMING_PIN number 
#endif
//***************************************************


#if SYNC_PIN == 13
const byte sync_pin = SYNC_PIN;		// B7
#define SetSyncPin   			PORTB |= (1 << PORTB7)  
#define ClearSyncPin   			PORTB &= ~(1 << PORTB7) 
#define ToggleSyncPin   		PINB = (1 << PINB7) 

#elif SYNC_PIN == 12
const byte sync_pin = SYNC_PIN;		// B6
#define SetSyncPin   			PORTB |= (1 << PORTB6)  
#define ClearSyncPin   			PORTB &= ~(1 << PORTB6) 
#define ToggleSyncPin   		PINB = (1 << PINB6) 

#elif SYNC_PIN == 8
const byte sync_pin = SYNC_PIN;		// H5
#define SetSyncPin   			PORTH |= (1 << PORTH5)  
#define ClearSyncPin   			PORTH &= ~(1 << PORTH5)
#define ToggleSyncPin   		PINH = (1 << PINH5) 

#elif SYNC_PIN == 7
const byte sync_pin = SYNC_PIN;		// H4
#define SetSyncPin   			PORTH |= (1 << PORTH4)  
#define ClearSyncPin  			PORTH &= ~(1 << PORTH4) 
#define ToggleSyncPin   		PINH = (1 << PINH4) 

#elif SYNC_PIN == 6
const byte sync_pin = SYNC_PIN;		// H3
#define SetSyncPin   			PORTH |= (1 << PORTH3)  
#define ClearSyncPin  			PORTH &= ~(1 << PORTH3) 
#define ToggleSyncPin   		PINH = (1 << PINH3) 

#elif !defined SYNC_PIN
#define SYNC_PIN MAX_TEST_PIN + 3
#define SetSyncPin   			 
#define ClearSyncPin  			
#define ToggleSyncPin   		 

#elif defined SYNC_PIN
#error Invalid SYNC_PIN number
#endif
//***************************************************

#if PROBE_PIN == 13
const byte probe_pin = PROBE_PIN;		// B7
#define SetProbePin   			PORTB |= (1 << PORTB7)  
#define ClearProbePin   		PORTB &= ~(1 << PORTB7) 
#define ToggleProbePin   		PINB = (1 << PINB7) 

#elif PROBE_PIN == 12
const byte probe_pin = PROBE_PIN;		// B6
#define SetProbePin   			PORTB |= (1 << PORTB6)  
#define ClearProbePin   		PORTB &= ~(1 << PORTB6) 
#define ToggleProbePin   		PINB = (1 << PINB6) 

#elif PROBE_PIN == 8
const byte probe_pin = PROBE_PIN;		// H5
#define SetProbePin   			PORTH |= (1 << PORTH5)  
#define ClearProbePin   		PORTH &= ~(1 << PORTH5)
#define ToggleProbePin   		PINH = (1 << PINH5) 

#elif PROBE_PIN == 7
const byte probe_pin = PROBE_PIN;		// H4
#define SetProbePin   			PORTH |= (1 << PORTH4)  
#define ClearProbePin  			PORTH &= ~(1 << PORTH4) 
#define ToggleProbePin   		PINH = (1 << PINH4) 

#elif PROBE_PIN == 6
const byte probe_pin = PROBE_PIN;		// H3
#define SetProbePin   			PORTH |= (1 << PORTH3)  
#define ClearProbePin  			PORTH &= ~(1 << PORTH3) 
#define ToggleProbePin   		PINH = (1 << PINH3) 

#elif !defined PROBE_PIN
#define PROBE_PIN MAX_TEST_PIN + 4
#define SetProbePin   			
#define ClearProbePin  			 
#define ToggleProbePin   		

#elif defined PROBE_PIN
#error Invalid PROBE_PIN number
#endif
//***************************************************

#if AUX_PIN == 13
const byte aux_pin = AUX_PIN;		// B7
#define SetAuxPin   			PORTB |= (1 << PORTB7)  
#define ClearAuxPin   			PORTB &= ~(1 << PORTB7) 
#define ToggleAuxPin   			PINB = (1 << PINB7) 

#elif AUX_PIN == 12
const byte aux_pin = AUX_PIN;		// B6
#define SetAuxPin   			PORTB |= (1 << PORTB6)  
#define ClearAuxPin   			PORTB &= ~(1 << PORTB6) 
#define ToggleAuxPin   			PINB = (1 << PINB6) 

#elif AUX_PIN == 8
const byte aux_pin = AUX_PIN;		// H5
#define SetAuxPin   			PORTH |= (1 << PORTH5)  
#define ClearAuxPin   			PORTH &= ~(1 << PORTH5)
#define ToggleAuxPin   			PINH = (1 << PINH5) 

#elif AUX_PIN == 7
const byte aux_pin = AUX_PIN;		// H4
#define SetAuxPin   			PORTH |= (1 << PORTH4)  
#define ClearAuxPin  			PORTH &= ~(1 << PORTH4) 
#define ToggleAuxPin   			PINH = (1 << PINH4) 

#elif AUX_PIN == 6
const byte aux_pin = AUX_PIN;		// H3
#define SetAuxPin   			PORTH |= (1 << PORTH3)  
#define ClearAuxPin  			PORTH &= ~(1 << PORTH3) 
#define ToggleAuxPin   			PINH = (1 << PINH3) 

#elif !defined AUX_PIN
#define AUX_PIN MAX_TEST_PIN + 5
#define SetAuxPin   		
#define ClearAuxPin  		 
#define ToggleAuxPin   		

#elif defined AUX_PIN
#error Invalid AUX_PIN number
#endif
