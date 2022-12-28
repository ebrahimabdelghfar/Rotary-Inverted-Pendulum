#include <Arduino.h>
#include "encoder_arduino.h"

typedef struct
{
    int pinA;
    int pinB;
    int pos;
    int del;
} Encoder;
volatile Encoder Enc[3] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

// Auxiliary function to handle encoder attachment
static int getIntNum(int pin)
{
    // Returns the interrupt number for a given interrupt pin
    // See http://arduino.cc/it/Reference/AttachInterrupt
    switch(pin) {
        case 2:
            return 0;
        case 3:
            return 1;
        case 21:
            return 2;
        case 20:
            return 3;
        case 19:
            return 4;
        case 18:
            return 5;
        default:
            return -1;
    }
}

// Auxiliary debouncing function
static void debounce(int del)
{
    for (int k = 0; k < del; k++) {
        // can't use delay in the ISR so need to waste some time
        // perfoming operations, this uses roughly 0.1ms on uno
        k = k +0.0 +0.0 -0.0 +3.0 -3.0;
    }
}

// Interrupt Service Routine: change on pin A for Encoder 0
static void irsPinAEn0(void)
{
    // Read pin B right away
    int drB = digitalRead(Enc[0].pinB);
    
    // Possibly wait before reading pin A, then read it
    debounce(Enc[0].del);
    int drA = digitalRead(Enc[0].pinA);
    
    // this updates the counter
    if (drA == HIGH)
    {
        // low->high on A?
        if (drB == LOW) {  // check pin B
            Enc[0].pos++;  // going clockwise: increment
        }
        else {
            Enc[0].pos--;  // going counterclockwise: decrement
        }
        
    }
    else {
        // must be high to low on A
        if (drB == HIGH) { // check pin B
            Enc[0].pos++;  // going clockwise: increment
        }
        else {
            Enc[0].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
} // end ISR pin A Encoder 0



// Interrupt Service Routine: change on pin B for Encoder 0
static void isrPinBEn0(void)
{
    // read pin A right away
    int drA = digitalRead(Enc[0].pinA);
    
    // possibly wait before reading pin B, then read it
    debounce(Enc[0].del);
    int drB = digitalRead(Enc[0].pinB);
    
    // this updates the counter
    if (drB == HIGH) {   // low->high on B?
        if (drA == HIGH) { // check pin A
            Enc[0].pos++;  // going clockwise: increment
        } else {
            Enc[0].pos--;  // going counterclockwise: decrement
        }
    } else {                       // must be high to low on B
        if (drA == LOW) {  // check pin A
            Enc[0].pos++;  // going clockwise: increment
        } else {
            Enc[0].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
} // end ISR pin B Encoder 0

// Interrupt Service Routine: change on pin A for Encoder 1
static void irsPinAEn1(void)
{
    // read pin B right away
    int drB = digitalRead(Enc[1].pinB);
    
    // possibly wait before reading pin A, then read it
    debounce(Enc[1].del);
    int drA = digitalRead(Enc[1].pinA);
    
    // this updates the counter
    if (drA == HIGH) {   // low->high on A?
        if (drB == LOW) {  // check pin B
            Enc[1].pos++;  // going clockwise: increment
        } else {
            Enc[1].pos--;  // going counterclockwise: decrement
        }
    } else { // must be high to low on A
        if (drB == HIGH) { // check pin B
            Enc[1].pos++;  // going clockwise: increment
        } else {
            Enc[1].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
    
} // end ISR pin A Encoder 1


// Interrupt Service Routine: change on pin B for Encoder 1
static void isrPinBEn1(void)
{
    // read pin A right away
    int drA = digitalRead(Enc[1].pinA);
    
    // possibly wait before reading pin B, then read it
    debounce(Enc[1].del);
    int drB = digitalRead(Enc[1].pinB);
    
    // this updates the counter
    if (drB == HIGH) {   // low->high on B?
        if (drA == HIGH) { // check pin A
            Enc[1].pos++;  // going clockwise: increment
        } else {
            Enc[1].pos--;  // going counterclockwise: decrement
        }
    } else { // must be high to low on B
        if (drA == LOW) {  // check pin A
            Enc[1].pos++;  // going clockwise: increment
        } else {
            Enc[1].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
    
} // end ISR pin B Encoder 1


// Interrupt Service Routine: change on pin A for Encoder 2
static void irsPinAEn2(void)
{
    // read pin B right away
    int drB = digitalRead(Enc[2].pinB);
    
    // possibly wait before reading pin A, then read it
    debounce(Enc[2].del);
    int drA = digitalRead(Enc[2].pinA);
    
    // this updates the counter
    if (drA == HIGH) {   // low->high on A?
        if (drB == LOW) {  // check pin B
            Enc[2].pos++;  // going clockwise: increment
        } else {
            Enc[2].pos--;  // going counterclockwise: decrement
        }
    }
    else { // must be high to low on A
        if (drB == HIGH) { // check pin B
            Enc[2].pos++;  // going clockwise: increment
        } else {
            Enc[2].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
    
} // end ISR pin A Encoder 2


// Interrupt Service Routine: change on pin B for Encoder 2
static void isrPinBEn2(void)
{
    // read pin A right away
    int drA = digitalRead(Enc[2].pinA);
    
    // possibly wait before reading pin B, then read it
    debounce(Enc[2].del);
    int drB = digitalRead(Enc[2].pinB);
    
    // this updates the counter
    if (drB == HIGH) {   // low->high on B?
        if (drA == HIGH) { // check pin A
            Enc[2].pos++;  // going clockwise: increment
        } else {
            Enc[2].pos--;  // going counterclockwise: decrement
        }
    }
    else { // must be high to low on B
        if (drA == LOW) {  // check pin A
            Enc[2].pos++;  // going clockwise: increment
        } else {
            Enc[2].pos--;  // going counterclockwise: decrement
        }
    } // end counter update
    
} // end ISR pin B Encoder 2

// Initialization function called by Encoder System object
extern "C" void enc_init(int enc, int pinA, int pinB)
{
    // enc is the encoder number and it can be 0,1 or 2
    // if other encoder blocks are present in the model
    // up to a maximum of 3, they need to refer to a
    // different encoder number
    
    // store pinA and pinB in global encoder structure Enc
    // they will be needed later by the interrupt routine
    // that will not be able to access s-function parameters
    
    Enc[enc].pinA=pinA;      // set pin A
    Enc[enc].pinB=pinB;      // set pin B
    
    // set encoder pins as inputs
    pinMode(Enc[enc].pinA, INPUT);
    pinMode(Enc[enc].pinB, INPUT);
    
    // turn on pullup resistors
    digitalWrite(Enc[enc].pinA, HIGH);
    digitalWrite(Enc[enc].pinB, HIGH);
    
    // attach interrupts
    switch(enc) {
        case 0:
            attachInterrupt(getIntNum(Enc[0].pinA), irsPinAEn0, CHANGE);
            attachInterrupt(getIntNum(Enc[0].pinB), isrPinBEn0, CHANGE);
            break;
        case 1:
            attachInterrupt(getIntNum(Enc[1].pinA), irsPinAEn1, CHANGE);
            attachInterrupt(getIntNum(Enc[1].pinB), isrPinBEn1, CHANGE);
            break;
        case 2:
            attachInterrupt(getIntNum(Enc[2].pinA), irsPinAEn2, CHANGE);
            attachInterrupt(getIntNum(Enc[2].pinB), isrPinBEn2, CHANGE);
            break;
    }
}

// Output function called by Encoder System object
extern "C" int enc_output(int enc)
{
    return (double)Enc[enc].pos;
}
// [EOF]

