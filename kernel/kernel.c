#include <kernel.h>

int kemain(multiboot_info_t* mb_info, u32 mb_magic)
{
    __asm__("xchg %bx, %bx");
    clear_screen();

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        xprintf("multiboot eax is not equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    } else {
        xprintf("multiboot eax is equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    }

    // idt_init();
    // timer_init(TIMER_HZ);
    // keyboard_init();

    puts(" __  __                                  ___    ____  \n");
    puts("|  \\/  |   ___    _ __ ___     ___      / _ \\  / ___| \n");
    puts("| |\\/| |  / _ \\  | '_ ` _ \\   / _ \\    | | | | \\___ \\ \n");
    puts("| |  | | | (_) | | | | | | | | (_) |   | |_| |  ___) |\n");
    puts("|_|  |_|  \\___/  |_| |_| |_|  \\___/     \\___/  |____/ \n");
    puts("\n=======================================================\n");

    setup_sys_param();

    xprintf("Memory Mapping using int 15h E820\n");
    // for (int i = 0; i < 6; ++i)
    //     xprintf("Base: %08X %08X Limit: %08X %08X Type: %08X \n",
    //             mem_map_entry[i].base_high,
    //             mem_map_entry[i].base_low,
    //             mem_map_entry[i].limit_high,
    //             mem_map_entry[i].limit_low,
    //             mem_map_entry[i].type);

    __asm__("sti");

    for (;;)
        ;
    return 0;
}
