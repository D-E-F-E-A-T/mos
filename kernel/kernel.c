#include <kernel.h>


int _kemain()
{
	clear_screen();
	idtr_setup();
	
	__asm__ ("sti");
	return 0;
}

