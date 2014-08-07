#include <kernel.h>


int _kemain()
{
	int i;
	char msg[] = "Hello \nWorld\n";

	clear_screen();
	idtr_setup();
	puts(msg);

	memset((char *)0x700000, 'x', 20);
	puts((char *)0x700000);

	// i = 1 / 0;
	__asm__ ("int $3");
	
	return 0;
}

