/*
 Name:		VS_new_Simple.ino
 Created:	9/4/2022 8:15:56 PM
 Author:	Mihai
*/

// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(115200);
    while (!Serial) {}

    Serial.println();    Serial.println();

    Serial.println(__cplusplus);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
