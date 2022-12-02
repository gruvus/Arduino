
byte mirror(byte v) { //reverse bits to see MSB to LSB on the scope
	byte r = 0;
	for (int i = 0; i < 8; i++) {
		bitWrite(r, i, bitRead(v, 7 - i));
	}
	return r;
}

const int byt = 0b11110000;

void loop_tx() {
	while (true) {
		//  Serial.print(x,BIN);
		//  Serial.write(0x10);
		Serial.write(mirror(byt));  //reverse bits to see MSB-to-LSB on the scope
		Serial.write(mirror(byt));

		//  delay(2);
		//  Serial.write(0xE8);

		//  Serial.println();
		//  Serial.println("Done");
		//
		//  Serial.end();
		delay(5);
	}
}
