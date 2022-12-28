#include <Arduino.h>
#include "aout_arduino.h"

extern "C" void aout_init(uint8_T pin) {   
    pinMode(pin, OUTPUT);
}

extern "C" void aout_output(uint8_T pin, uint8_T val) {
    analogWrite(pin, val);
}
// [EOF]

