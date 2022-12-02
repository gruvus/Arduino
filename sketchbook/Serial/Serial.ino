/*
	Name:       Serial.ino
	Created:	9/6/2022 11:29:05 PM
	Author:     HEX10\Mihai
	loop to visualize signal output (TX / pin 1)
 *
 */

void setup() {
	Serial.begin(115200
); // open the serial port at ... bps:

	Serial.print("\n\n\n");

	//loop_tx();

	print_all_codes();

}



void loop() {


}