/**
 * IO Port Operations
 */
#ifndef PORT_H
#define PORT_H

#include <int.h>

// form 44 entOS
// inline enabled by default
u8 inportb(u16 port);

u16 inportw(u16 port);

void outportb(u16 port, u8 data);

void outportw(u16 port, u16 data);

void io_wait();

#endif