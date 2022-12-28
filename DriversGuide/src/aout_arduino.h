#ifndef _AOUT_ARDUINO_H_
#define _AOUT_ARDUINO_H_
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif
    
void aout_init(uint8_T pin);
void aout_output(uint8_T pin, uint8_T in);

#ifdef __cplusplus
}
#endif
#endif // _AOUT_ARDUINO_H_
