
byte mirror(byte v) { //reverse bits to see MSB to LSB on the scope
	byte r = 0;
	for (int i = 0; i < 8; i++) {
		bitWrite(r, i, bitRead(v, 7 - i));
	}
	return r;
}

void printBits(uint8_t v) {
	const byte N = 8;
	//Serial.print("        ");
	Serial.print("........");

	for (int i = N - 1; i >= 0; i--) {
		Serial.print(bitRead(v, i));
	}
}


void printBits(uint16_t v) {
	const byte N = 16;
	for (int i = N - 1; i >= 0; i--) {
		Serial.print(bitRead(v, i));
	}
}


void printBits(uint32_t v) {
	const byte N = 32;
	for (int i = N - 1; i >= 0; i--) {
		Serial.print(bitRead(v, i));
	}
}

void printBits(int v) {
	const byte N = 16;
	for (int i = N - 1; i >= 0; i--) {
		Serial.print(bitRead(v, i));
	}
}

void printBits(long v) {
	const byte N = 32;
	Serial.print("........");	Serial.print("........");
	for (int i = N - 1; i >= 0; i--) {
		Serial.print(bitRead(v, i));
	}
}


void setup() {

	Serial.begin(115200); Serial.print("\n");
	Serial.print("===============================\n");
	Serial.print("   Running ~Sketch (in A_08)\n");
	Serial.print("===============================\n"); Serial.print("\n\n");

	{
		uint16_t v = 0b10011001;
		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
	}
	{
		byte v = 0xf0;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = -1;				Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
	}

	{
		int v = 0xff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0xffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
	}

	{
		long v = 0xff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0xffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0xffffffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0x8fffffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0x7fffffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
	}

	{
		unsigned long v = 0xff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0xffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0xffffffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
		v = 0x8fffffff;		Serial.print("\t");	Serial.print(v);	Serial.print("\t");	printBits(v);	Serial.print("\t");	Serial.print(v, BIN);	Serial.print("\n");
	}



}

void loop() {

}
