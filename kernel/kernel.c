

#include <kernel.h>

int _kemain()
{

	char msg[] = "Hello \nWorld\n";


	clear_screen();
	puts(msg);

	puts("start memset\n");
	memset((char *)0xFFFF0000, 'x', 20);
	puts((char *)0xFFFF0000);
	
	return 0;
}

