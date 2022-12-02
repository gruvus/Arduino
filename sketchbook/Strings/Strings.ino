

//char  array[100] = "asdfgh"; //the max. string length is 11 characters
// and Null as string-terminator



void setup() {

	Serial.begin(115200);
	Serial.print(" Running: Strings and chars samples \n");
	Serial.print("====================================\n\n");


	Sample_1();

	Serial.print("\n====================================\n\n");
	Serial.print("\n Finished\n\n");

}

void loop() {}


void Sample_2() {
	char* msg = "Initial string of characters.";

	int len = strlen(msg);

	Serial.print(msg);	Serial.print("\t"); Serial.print(len); Serial.print("\n");


	for (int i = 0; i < len; i++) {
		Serial.print(i); Serial.print("\t");
		Serial.print(msg[i]); Serial.print("\t");
		Serial.print((int)msg[i]); Serial.print("\t");
		Serial.print("\n");
		Serial.flush();

	}

	Serial.println();

	int v = msg[len];
	Serial.print(v);

	Serial.print("\n");



	char* r_msg = msg + 2;

	Serial.println(msg);

	Serial.println(r_msg);
	Serial.println(msg + 2);
}

void Sample_1() {

	//from https://forum.arduino.cc/t/char-array-handling-guide-for-beginners/496148
	Serial.print("\n char array handling guide for beginners");
	Serial.print("\n=========================================\n\n");

	char  array[12] = "asdfgh"; //the max. string length is 11 characters + Null terminator


	//String manipulations
	Serial.println(array);    //-> asdfgh
	Serial.println(array[2]); //-> d
	Serial.println(array + 2);  //-> dfgh
	//but following generate compiler error
	//array+=2; //incompatible types in assignment of 'int' to 'char [10]'
	strcpy(array, "hallo");
	Serial.println(array);    //-> hallo

	strcpy(array, "");
	Serial.println(array);    //->

	strcpy(array, "23456789");
	Serial.println(array);    //-> 23456789
	Serial.println(strcpy(array, "23456789"));    //-> 23456789

	strncpy(array, "hallo", 2); //!!!see 2 lines later
	Serial.println(array);    //-> ha456789

	array[2] = '\0';  //terminator neccessary
	Serial.println(array);    //-> ha

	strcat(array, "567");
	Serial.println(array);    //-> ha567

	strncat(array, array, 3);
	Serial.println(array);    //-> ha567ha5

	strcpy(array, array + 3);
	Serial.println(array);    //-> 67ha5

	//add bytewise inputs to char array
	Serial.println("");
	Serial.println("Bytewise add:");
	char InputChar = 'a';							// byte InputChar = 'a';	
	byte InputInt = 108; //108 ist the char 'l'	// uint8_t  InputInt = 108;
	int   i;
	strcpy(array, "test");
	Serial.println(array);    //-> test

	i = strlen(array);
	array[i++] = InputChar; // put InputChar at location i & increment i
	array[i] = '\0';  // allways terminate strings
	Serial.println(array);    //-> testa

	array[i++] = InputInt;  //this overwrites last written terminator
	array[i] = '\0';  //new string terminator
	Serial.println(array);    //-> testal
}

