/*
	Name:       Random.ino
	Created:	9/5/2022 10:05:20 PM
	Author:     HEX10\Mihai
*/


#include "limits.h"

#ifndef ARDUINO_SAM_DUE
typedef unsigned int uint;
#endif


void setup()
{
	// start up 
	Serial.begin(115200);
	// print splash 
	{
		Serial.print("\n");
		Serial.println("\n********* Study project: Random ****************\n");

		Serial.print("\tBoard:  \t");
#ifdef ARDUINO_SAM_DUE
		Serial.print("DUE");
#else
		Serial.println("UNO");
		typedef unsigned int uint;
#endif
		Serial.print("\n");
		Serial.print("\tINT_MAX: \t"); Serial.println(INT_MAX);
		Serial.print("\tLONG_MAX:\t"); Serial.println(LONG_MAX);
		Serial.println("\n************************************************\n");
		Serial.flush();
	}

	uint a = INT_MAX, b = INT_MAX;
	Serial.print("1\t"); Serial.println(INT_MAX); Serial.flush();
	Serial.print("2\t"); Serial.println(a); Serial.flush();
	a = 2 * INT_MAX;
	Serial.print("3\t"); Serial.println(a); Serial.flush();
	Serial.print("4\t"); Serial.println(2 * INT_MAX); Serial.flush();
	Serial.print("5\t"); Serial.println(2 * b); Serial.flush();
	Serial.print("6\t"); Serial.println(2 * (uint)INT_MAX); Serial.flush();
	Serial.print("7\t"); Serial.println(2U * INT_MAX); Serial.flush();


	srand(3);

	// one time tasks
	last_digit_distribution();
}

void loop()
{


}
