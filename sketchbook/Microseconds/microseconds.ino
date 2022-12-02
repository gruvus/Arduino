/*
	what is the resolution of the micros() function on Due vs Uno
*/


void loop() {
	static int pass = 1;
	Serial.print("Pass: "); Serial.print(pass);	Serial.print("\n");

	// micros_delay_resolution();
	//test_random_numbers();

	while (pass>=1) {} // block here
	//// never gets out
	//Serial.println("Impossible: Exiting loop()");
	pass++;

}


void setup() {
	Serial.begin(115200);
	Serial.println();    Serial.println();

	last_digit_distribution();

}

