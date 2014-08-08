#include <kernel.h>


int _kemain()
{
	int i;
	char msg[] = "Hello \nWorld\n";

	clear_screen();
	idtr_setup();
	puts(msg);

	xprintf("hello %d\n", 99);

	// i = 1 / 0;
	__asm__ ("int $0x20");
	
	return 0;
}

