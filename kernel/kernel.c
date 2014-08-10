#include <kernel.h>


int _kemain()
{
	char msg[] = "Hello \nWorld\n";

	clear_screen();
	idtr_setup();
	puts(msg);

	xprintf("hello %d\n", 99);
	
	__asm__ ("sti");
	return 0;
}

