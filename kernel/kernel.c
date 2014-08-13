#include <kernel.h>



int _kemain()
{
	u32 *entry_count = (u32 *)0x500;

	
	clear_screen();
	idt_init();
	timer_init(TIMER_HZ);
	keyboard_init();

	puts(" __  __                                  ___    ____  \n");
	puts("|  \\/  |   ___    _ __ ___     ___      / _ \\  / ___| \n");
	puts("| |\\/| |  / _ \\  | '_ ` _ \\   / _ \\    | | | | \\___ \\ \n");
	puts("| |  | | | (_) | | | | | | | | (_) |   | |_| |  ___) |\n");
	puts("|_|  |_|  \\___/  |_| |_| |_|  \\___/     \\___/  |____/ \n");
	puts("\n=======================================================\n");	
	xprintf("number of entry = %d\n", *entry_count);
	
	__asm__ ("sti");
	return 0;
}

