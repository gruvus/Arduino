
bool first_pass = true;
//===========================================================

void loop() {
	//build values table
	build_values();
	test_print_values();

	// cycle through values table
	Serial.print("Generating "); print_wave_name(); Serial.print(" wave with "); Serial.print(OUT_STEPS); Serial.print(" steps\n");

	while (true) { // cycle through values
		if (first_pass && VERBOSE) Serial.print("\nAscending\n");

		//if (BLINK)	digitalWrite(LED_PIN, HIGH); // too early

		for (int i = 0; i < OUT_MAX; i++) {   // ascending
			analogWrite(DAC_PIN, values[i]);					// tho output takes longer
			if (i == 0 && BLINK)  digitalWrite(LED_PIN, HIGH);	// right after
			//digitalWrite(LED_PIN, HIGH);
			if (first_pass && VERBOSE) {
				int v = values[i];
				Serial.print(i); Serial.print("\t\t\t");
				Serial.print(v); Serial.print("\n");
			}
		}

		//if (BLINK)	digitalWrite(LED_PIN, LOW);

		if (first_pass && VERBOSE) Serial.print("\nDescending\n");

		for (int j = OUT_MAX; j > 0; j--) {   // descending
			analogWrite(DAC_PIN, values[j]);
			if (j == OUT_MAX && BLINK)	digitalWrite(LED_PIN, LOW);
			//digitalWrite(LED_PIN, LOW);
			if (first_pass && VERBOSE) {
				int v = values[j];
				Serial.print(j); Serial.print("\t");
				Serial.print(j); Serial.print("\t\t");
				Serial.print(v); Serial.print("\n");
			}
		}
		first_pass = false;
	}
	// should never get here
	Serial.println("should never get here");
	first_pass = false;
}
