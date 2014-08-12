#ifndef TIMER_H
#define TIMER_H

#include <port.h>
#include <pic8259.h>
#include <datetime.h>
#include <printf.h>

#define PIT_CHANNEL0		(0x40)  // PIT Channel 0's Data Register Port
#define PIT_CHANNEL1		(0x41)  // PIT Channels 1's Data Register Port, we wont be using this here
#define PIT_CHANNEL2		(0x42)  // PIT Channels 2's Data Register Port
#define PIT_CMDREG			(0x43)  // PIT Chip's Command Register Port

#define PIT_TICK_RATE		(1193180)
#define TIMER_HZ			(100)	// valid value between 18 and 65536

void timer_set(int hz);
void timer_init(int hz);

void enable_timer();
void disable_timer();

void timer_handler();

#endif