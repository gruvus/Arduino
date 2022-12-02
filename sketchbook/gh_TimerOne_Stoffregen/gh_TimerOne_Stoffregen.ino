// https://github.com/PaulStoffregen/TimerOne

#include "TimerOne.h"
#include "utils.h"
#include "T1_setup.h"


#define EXAMPLE_INTERRUPT

//#define EXAMPLE_FANSPEED

extern TimerOne Timer1;


#ifdef EXAMPLE_INTERRUPT


// This example uses the timer interrupt to blink an LED
// and also demonstrates how to share a variable between
// the interrupt and the main program.

const int led = LED_BUILTIN;  // the pin with a LED

void setup(void)
{
    pinMode(led, OUTPUT);
	Timer1.initialize(50000);
    Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
    Serial.begin(115200);

    ShowConfig_T1("\nsetup> ");

}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void blinkLED(void)
{
    if (ledState == LOW) {
        ledState = HIGH;
        blinkCount = blinkCount + 1;  // increase when LED turns on
    }
    else {
        ledState = LOW;
    }
    digitalWrite(led, ledState);
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
    unsigned long blinkCopy;  // holds a copy of the blinkCount

    // to read a variable which the interrupt code writes, we
    // must temporarily disable interrupts, to be sure it will
    // not change while we are reading.  To minimize the time
    // with interrupts off, just quickly make a copy, and then
    // use the copy while allowing the interrupt to keep working.
    noInterrupts();
    blinkCopy = blinkCount;
    interrupts();

    Serial.print("blinkCount = ");
    Serial.println(blinkCopy);

    static byte first_pass = 1;
    
    if (first_pass) ShowConfig_T1("\nloop> ");
    
    first_pass = 0;
    
    delay(1000);

}

#else
#ifdef EXAMPLE_FANSPEED


// This example creates a PWM signal with 25 kHz carrier.
//
// Arduino's analogWrite() gives you PWM output, but no control over the
// carrier frequency.  The default frequency is low, typically 490 or
// 3920 Hz.  Sometimes you may need a faster carrier frequency.
//
// The specification for 4-wire PWM fans recommends a 25 kHz frequency
// and allows 21 to 28 kHz.  The default from analogWrite() might work
// with some fans, but to follow the specification we need 25 kHz.
//
// http://www.formfactors.org/developer/specs/REV1_2_Public.pdf
//
// Connect the PWM pin to the fan's control wire (usually blue).  The
// board's ground must be connected to the fan's ground, and the fan
// needs +12 volt power from the computer or a separate power supply.

const byte fanPin = 10;  // pin 9 or 10 // controlled by Timer1 (UNO)
const byte altPin = 9;

void setup(void)
{
    Timer1.initialize((65535/8));  // 40 us = 25 kHz
    Serial.begin(115200);

    ShowConfig_T1("<setup>");

    //Timer1.pwm(fanPin, 1023);
    Timer1.pwm(fanPin, 1);

    Timer1.pwm(altPin, 512);


    Show16bitRegisters_T1();


}

void loop(void)
{

/*

    // slowly increase the PWM fan speed
    //
    for (int i = 0; i <= 10; i++) {

        int dutyCycle = i*1;
        Serial.print("\n *********** PWM Fan, Duty Cycle = ");   Serial.print(dutyCycle); Serial.print("\n\n");
        Timer1.pwm(fanPin, (dutyCycle / 100.0) * 1023);   //mm ? : expects value between 0 and 1023 (10bit integer)
        //ShowConfig_T1("<loop>");
        Show16bitRegisters_T1();

        delay(10000);
    }
    //for (float dutyCycle = 100.0; dutyCycle >0; dutyCycle--) {
    //    Serial.print("PWM Fan, Duty Cycle = ");
    //    Serial.println(dutyCycle);
    //    Timer1.pwm(fanPin, (dutyCycle / 100) * 1023);
    //    delay(5000);
    //}
*/

}
#endif // EXAMPLE_FANSPEED

#endif // EXAMPLE_INTERRUPT