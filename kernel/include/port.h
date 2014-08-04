/*
	Abstration of port operations.
*/
#ifndef PORT_H
#define PORT_H

#include <int.h>

static inline uint8 inb(uint16 port)
{
	uint8 ret;
	asm volatile (
		"inb %%dx, %%al"
		: "=a"	(ret)
		: "d"	(port));

	return ret;
}

static inline uint16 inw(uint16 port)
{
	uint16 ret;
	asm volatile (
		"inb %%dx, %%al"
		: "=a"	(ret)
		: "d"	(port));

	return ret;
}

static inline void outb(uint16 port, uint8 data)
{
	asm volatile (
		"outb %%al, %%bx"
		: : "a" (data)
		: "b"	(port)
		)
}

static inline void outw(uint16 port, uint16 data)
{
	asm volatile (
		"outw %%ax, %%bx"
		: : "a" (data)
		: "b"	(port)
		)
}

#endif