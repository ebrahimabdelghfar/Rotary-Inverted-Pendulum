#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "rtwtypes.h"


void writeServoBlaster(int channel, int value)
{
    int fd, len;
	char buf[16];
    
    // Check that channel number is between 0 and 7. According to ServoBlaster documentation,
    // here is the mapping from channel numbers to GPIO pins:
    //
    // Servo mapping:
    // 0 on P1-7           GPIO-4
    // 1 on P1-11          GPIO-17
    // 2 on P1-12          GPIO-18
    // 3 on P1-13          GPIO-27
    // 4 on P1-15          GPIO-22
    // 5 on P1-16          GPIO-23
    // 6 on P1-18          GPIO-24
    // 7 on P1-22          GPIO-25
    if ((channel < 0) || (channel > 7)) {
        return;
    }
    
    fd = open("/dev/servoblaster", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("servoblaster/open");
        return;
    }
    
    // Limit value to between 0 and 100
    value = value < 0 ? 0:value;
    value = value > 100 ? 100:value;
    
    // Write value to ServoBlaster device file
    len = snprintf(buf, 15, "%d=%d%%\n", channel, value);
    write(fd, buf, len);
    close(fd);
}
// [EOF]