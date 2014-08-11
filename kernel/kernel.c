#include <kernel.h>


int _kemain()
{
	clear_screen();
	idt_init();
	timer_init(TIMER_HZ);
	keyboard_init();

	__asm__ ("xchg %bx, %bx");
	puts(" __  __                                  ___    ____  \n");
	puts("|  \\/  |   ___    _ __ ___     ___      / _ \\  / ___| \n");
	puts("| |\\/| |  / _ \\  | '_ ` _ \\   / _ \\    | | | | \\___ \\ \n");
	puts("| |  | | | (_) | | | | | | | | (_) |   | |_| |  ___) |\n");
	puts("|_|  |_|  \\___/  |_| |_| |_|  \\___/     \\___/  |____/ \n");
	puts("\n=======================================================\n");

	__asm__ ("sti");
	return 0;
}

