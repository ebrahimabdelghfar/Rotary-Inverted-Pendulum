#ifndef _ENCODER_RASPI_H_
#define _ENCODER_RASPI_H_
#include "rtwtypes.h"

void encoderInit(uint8_T num, uint8_T pinA, uint8_T pinB);
int32_T encoderOutput(uint8_T num);
void encoderTerminate(uint8_T num);

#endif //_ENCODER_RASPI_H_
