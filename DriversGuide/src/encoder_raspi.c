#include "encoder_raspi.h"
#include "wiringPi.h"
#include <stdio.h>
#include <stdlib.h>

struct Encoder_t {
    uint8_T Num;
    uint8_T PinA;
    uint8_T PinB;
    int32_T Position;
    uint8_T LastReading;
    struct Encoder_t *Next;
};

typedef struct Encoder_t Encoder; 
Encoder *encList = NULL;

static int32_T EncLookup[16] = 
{
    0, // 0b0000
   -1, // 0b0001
   +1, // 0b0010
    0, // 0b0011
   +1, // 0b0100
    0, // 0b0101
    0, // 0b0110
   -1, // 0b0111
   -1, // 0b1000
    0, // 0b1001
    0, // 0b1010
   +1, // 0b1011
    0, // 0b1100
   +1, // 0b1101
   -1, // 0b1110
    0, // 0b1111
};

// Encoder interrupt service routine
static void encoderISR(void)
{
    int state, reading;
    Encoder *enc;
    
    // Update encoder positions
    for (enc = encList; enc != NULL; enc = enc->Next) {
        reading = digitalRead(enc->PinB) | (digitalRead(enc->PinA) << 1);
        state = (enc->LastReading << 2) | reading;
        enc->Position += EncLookup[state];
        enc->LastReading = reading;
    }
}

// Function used to lookup encoder object based on encoder number
static Encoder *lookupEncoder(uint8_T num)
{
    Encoder *enc;
    
    // Remove encoder from linked list and de-allocate storage
    enc = encList;
    while ((enc != NULL) && (enc->Num != num)) {
        enc = enc->Next;
    }

    return enc;
}

// Encoder initialization 
void encoderInit(uint8_T num, uint8_T pinA, uint8_T pinB)
{
    Encoder *newEnc;
    static int wiringPiInitialized = 0;
    
    // Initialize wiringPi if not done already
    if (!wiringPiInitialized) {
        wiringPiSetupGpio(); // Use Broadcom GPIO pin numbers
        wiringPiInitialized = 1;
    }
    
    // Create a new encoder
    newEnc = (Encoder *)malloc(sizeof(Encoder));
    if (newEnc == NULL) {
        perror("encoderInit/Memory allocation error");
        exit(-1);
    }
    
    // Initialize encoder parameters
    newEnc->Num         = num;
    newEnc->PinA        = pinA;
    newEnc->PinB        = pinB;
    newEnc->Position    = 0;
    newEnc->LastReading = 0;
    newEnc->Next        = NULL;
    
    // Install ISR service routine that will update encoder position
    pinMode(newEnc->PinA, INPUT);
    pinMode(newEnc->PinB, INPUT);
    pullUpDnControl(newEnc->PinA, PUD_UP);
    pullUpDnControl(newEnc->PinB, PUD_UP);
    wiringPiISR(newEnc->PinA, INT_EDGE_BOTH, &encoderISR);
    wiringPiISR(newEnc->PinB, INT_EDGE_BOTH, &encoderISR);
    newEnc->LastReading = digitalRead(newEnc->PinB) | (digitalRead(newEnc->PinA) << 1);
    
    // Add to encoder list
    if (encList == NULL) {
        encList = newEnc;
    }
    else {
        Encoder *enc = encList;
        while(enc->Next != NULL) {
            enc = enc->Next;
        }
        enc->Next = newEnc;
    }
}

// Returns encoder position
int32_T encoderOutput(uint8_T num)
{
    Encoder *enc;
    
    enc = lookupEncoder(num);
    
    return (enc->Position);
}

// Terminate encoder
void encoderTerminate(uint8_T num)
{
    Encoder *enc, *prevEnc;
    
    if (encList == NULL) {
        return;
    }
    
    // Remove encoder from linked list and de-allocate storage
    enc = encList;
    while ((enc != NULL) && (enc->Num != num)) {
        prevEnc = enc;
        enc = enc->Next;
    }
    if (enc == NULL) {
        return;
    }
    
    // Disable pull-ups
    pullUpDnControl(enc->PinA, PUD_OFF);
    pullUpDnControl(enc->PinB, PUD_OFF);
    
    // Remove encoder from list
    prevEnc->Next = enc->Next;
    free(enc);
}
// [EOF]