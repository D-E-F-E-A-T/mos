#include <kernel.h>

extern void gdt_setup();

int kemain(multiboot_info_t* mb_info, u32 mb_magic)
{
    clear_screen();

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        xprintf("multiboot eax is not equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    } else {
        xprintf("multiboot eax is equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    }

    gdt_setup();

    idt_init();
    timer_init(TIMER_HZ);
    keyboard_init();

    puts(" __  __                                  ___    ____  \n");
    puts("|  \\/  |   ___    _ __ ___     ___      / _ \\  / ___| \n");
    puts("| |\\/| |  / _ \\  | '_ ` _ \\   / _ \\    | | | | \\___ \\ \n");
    puts("| |  | | | (_) | | | | | | | | (_) |   | |_| |  ___) |\n");
    puts("|_|  |_|  \\___/  |_| |_| |_|  \\___/     \\___/  |____/ \n");
    puts("\n=======================================================\n");

    pmm_show(mb_info);

    __asm__("sti");

    for (;;)
        ;
    return 0;
}