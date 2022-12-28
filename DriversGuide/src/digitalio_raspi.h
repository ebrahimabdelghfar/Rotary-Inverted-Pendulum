#ifndef _DIGITAL_IO_RASPI_H_
#define _DIGITAL_IO_RASPI_H_
#include "rtwtypes.h"
    
void digitalIOSetup(uint8_T pin, boolean_T mode);
boolean_T readDigitalPin(uint8_T pin);
void writeDigitalPin(uint8_T pin, boolean_T val);

#endif //_DIGITAL_IO_RASPI_H_