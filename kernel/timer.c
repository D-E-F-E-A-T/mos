#include <timer.h>


void timer_set(int hz)
{
    int divisor = 1193180 / hz;       
    outportb(PIT_CMDREG, 0x36);             
    outportb(PIT_CHANNEL0, divisor & 0xFF);   
    outportb(PIT_CHANNEL0, divisor >> 8);  
}
