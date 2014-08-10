#ifndef TIMER_H
#define TIMER_H

#include <port.h>
#include <pic8259.h>

#define PIT_CHANNEL0		0x40  // PIT Channel 0's Data Register Port
#define PIT_CHANNEL1		0x41  // PIT Channels 1's Data Register Port, we wont be using this here
#define PIT_CHANNEL2		0x42  // PIT Channels 2's Data Register Port
#define PIT_CMDREG			0x43  // PIT Chip's Command Register Port

void timer_set(int hz);

void enable_timer(int hz);
void disable_timer();

#endif