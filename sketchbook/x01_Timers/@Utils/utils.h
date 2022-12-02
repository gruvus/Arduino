
// utils.h

#ifndef _UTILS_h
#define _UTILS_h


#include "arduino.h"

#include "utils_io.h"
#include "utils_bits.h"


#define lst(a) Serial.print(a)
#define TAB Serial.print("\t");
#define NL Serial.print("\n");
#define sflush Serial.flush();

#define tab TAB
#define ltb TAB
#define NewLine NL
#define nl NL
//#define flush Serial.flush()



//#define DBG
#ifdef DBG
#define DebugPrint(a) Serial.print(a)
#define dpr(a) Serial.print(a)
#define dprc(a,b) Serial.print(a,b)
#define dflush Serial.flush()
#define dtb TAB
#define dnl NL
#define dstop while(true){}


#else
#define DebugPrint(a)
#define dpr(a)
#define dprc(a,b)
#define dflush
#define dtb
#define dnl
#define dstop


#endif // DBG


#define logic(a) ( (a)?("true"):("false") )

const uint16_t UMAX16 = 65535;


typedef unsigned long ulong;
typedef void (*voidFuncPtr)(void);


void Action_Nothing();

void dlyMicros(ulong delay_time);


#endif	// #ifndef _UTILS_h



