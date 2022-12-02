

//===============================
void print_wave_name() {
	switch (wave_form) {
	case TRIANGLE:  Serial.print("TRIANGLE");   break;
	case SINE:      Serial.print("SINE");       break;
	case SQUARE:    Serial.print("SQUARE");     break;
	case BURST:     Serial.print("BURST");      break;
	case TEST:      Serial.print("TEST");       break;
	case RANDOM:    Serial.print("RANDOM");     break;
	default:        Serial.print("<"); Serial.print(wave_form); Serial.print(">"); break;
	}
}

//===============================
void test_print_values() {

	Serial.println("List values:");

	for (int i = 0; i <= OUT_MAX; i++) {
		Serial.print(" ");
		Serial.print(i);	Serial.print("\t");
		Serial.print(values[i]);	Serial.print("\t");
		Serial.print("\n");
	}
	Serial.print("\n");

}


