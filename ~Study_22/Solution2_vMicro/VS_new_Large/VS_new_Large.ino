/*
 Name:		VS_new_Large.ino
 Created:	9/4/2022 8:21:56 PM
 Author:	Mihai
*/

#include "vs_addnew_vm_cpppair.h" 
#include "src\vs_addnew_vm_cpppair_src.h"
#include "srcxtra\man_cpppair_srcxtra.h"


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	funcM();	// in main project ino file
	funcA();	// vm_A.ino
	funcB();	// src\vm_B.ino 

	funcC();	// vm_addnew_cpp_pair.cpp				(with vm_addnew_cpp_pair.h) 
	funcD();	// src\vs_addnew_vm_cpppair_src.cpp		(with src\vs_addnew_vm_cpppair_src.h) 
	funcE();	// srcxtra\man_cpppair_srcxtra.cpp		(with srcxtra\man_cpppair_srcxtra.h)

}


// the loop function runs over and over again until power down or reset
void loop() {


  
}

void funcM() {

	Serial.println("\n\tFunction M in file VS_new_Large.ino");

}