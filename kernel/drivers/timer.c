#include <timer.h>


void timer_set(int hz)
{
    int divisor = 1193180 / hz;       
    outportb(PIT_CMDREG, 0x36);             
    outportb(PIT_CHANNEL0, divisor & 0xFF);   
    outportb(PIT_CHANNEL0, divisor >> 8);  
}

void enable_timer(int hz)
{
	_enable_irq(0);
	timer_set(hz);
}

void disable_timer()
{
	_disable_irq(0);
}