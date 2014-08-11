#include <timer.h>


void timer_set(int hz)
{
    int divisor = PIT_TICK_RATE / hz;       
    outportb(PIT_CMDREG, 0x36);             
    outportb(PIT_CHANNEL0, divisor & 0xFF);   
    outportb(PIT_CHANNEL0, divisor >> 8);  
}

void timer_init(int hz)
{
	timer_set(hz);
	enable_timer(hz);
}

void enable_timer()
{
	_enable_irq(0);
}

void disable_timer()
{
	_disable_irq(0);
}