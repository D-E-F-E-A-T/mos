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

    xprintf("Memory Mapping using int 15h E820\n");
    multiboot_memory_map_t* mem_map_entry = (multiboot_memory_map_t*)mb_info->mmap_addr;

    while (mem_map_entry < (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length)) {

        xprintf("Base: %08X %08X Limit: %08X %08X Type: %08X \n",
                mem_map_entry->addr_high,
                mem_map_entry->addr_low,
                mem_map_entry->len_high,
                mem_map_entry->len_low,
                mem_map_entry->type);

        mem_map_entry++;
    }

    __asm__("sti");

    for (;;)
        ;
    return 0;
}