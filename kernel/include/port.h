/*
	Abstration of port operations.
*/
#ifndef PORT_H
#define PORT_H

#include <int.h>

// form 44 entOS
inline u8 inportb(u16 port);

inline u16 inportw(u16 port);

inline void outportb(u16 port, u8 data);

inline void outportw(u16 port, u16 data);

#endif