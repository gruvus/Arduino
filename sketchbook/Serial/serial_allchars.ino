/*
  print numbers in various formats.
*/

const char TAB = 9;
const char CR = 10;

void print_header() {
    // print labels
    Serial.println();
    Serial.print("NO FMT");  // prints a label
    Serial.print("\t");         // prints a tab

    Serial.print("DEC");
    Serial.print("\t");

    Serial.print("HEX");
    Serial.print("\t");

    Serial.print("OCT");
    Serial.print("\t");

    Serial.print("BIN");
    Serial.print("\t");

    Serial.print("CHAR");
    Serial.print(TAB);

    Serial.print("TEST");
    Serial.print("\n");        // carriage return after the last label

}

void print_all_codes() {
    const int base = 32;
    char c;
    for (int x = 1; x < 128; x++) { // only part of the ASCII chart, change to suit
        if ((x % base) == 0) {
            print_header();
        }
        // print it out in many formats:
        Serial.print(x);       // print as an ASCII-encoded decimal - same as "DEC"
        Serial.print("\t");  // prints two tabs to accomodate the label lenght

        Serial.print(x, DEC);  // print as an ASCII-encoded decimal
        //Serial.print("\t");    // prints a tab
        //Serial.print(char(9));  // also prints a tab
        Serial.print(TAB);      // also prints a tab

        Serial.print(x, HEX);  // print as an ASCII-encoded hexadecimal
        Serial.print("\t");    // prints a tab

        Serial.print(x, OCT);  // print as an ASCII-encoded octal
        Serial.print("\t");    // prints a tab

        Serial.print(x, BIN);  // print as an ASCII-encoded binary
        Serial.print("\t");
        c = x;
        Serial.print(c);  // print as a char
        Serial.print(TAB);

        Serial.print("abcd");

        //Serial.print("\n");    // prints a CR (same as "println")
        Serial.print(CR);    // also prints a CR (same as "println")

        //delay(200);            // delay 200 milliseconds
        Serial.flush();
    }
    Serial.println();        // prints another carriage return
    //Serial.end();
    while (true); //stop
}