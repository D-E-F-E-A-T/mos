#include <port.h>

// form 44 entOS
u8 inportb(u16 port) 
{
    u8 ret;
    __asm__ __volatile__ ("inb %1, %0":"=a"(ret):"dN"(port));
    return ret;
}

u16 inportw(u16 port) 
{
    u16 ret;
    __asm__ __volatile__ ("inw %1, %0":"=a"(ret):"dN"(port));
    return ret;
}

void outportb(u16 port, u8 data) 
{
    __asm__ __volatile__ ("outb %1, %0"::"dN"(port),"a"(data));
}

void outportw(u16 port, u16 data) 
{
    __asm__ __volatile__ ("outw %1, %0"::"dN"(port),"a"(data));
}

void io_wait()
{
	__asm__ __volatile__ ("out %%al, $0x80" :: "a"(0));
}	