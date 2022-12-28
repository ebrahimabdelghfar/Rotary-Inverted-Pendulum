#include <wiringPi.h>
#include "digitalio_raspi.h"

// Digital I/O initialization
void digitalIOSetup(uint8_T pin, boolean_T mode)
{
    static int initialized = false;
    
    // Perform one-time wiringPi initialization
    if (!initialized) {
        wiringPiSetupGpio();
        initialized = 1;
    }
    
    // mode = 0: Input
    // mode = 1: Output
    if (mode) {
        pinMode(pin, OUTPUT);
    }
    else {
        pinMode(pin, INPUT);
    }
}

// Read logical state of a digital pin
boolean_T readDigitalPin(uint8_T pin)
{
    return ((boolean_T)digitalRead(pin));
}

// Write a logic value to pin
void writeDigitalPin(uint8_T pin, boolean_T val)
{
    digitalWrite(pin, val);
}
// [EOF]