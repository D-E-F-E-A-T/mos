#include <kernel.h>

/*void dump_info()
{
    int cr0 = _keGetCR0();
    int cr3 = _keGetCR3();

    xprintf("cr0 = %08X, cr3 = %08X\n", cr0, cr3);
}*/

extern multiboot_info_t *mb_info_ptr;

__attribute__((section(".init.text"))) int keinit(u32 mb_magic)
{
    u32 cr0;
    u32 kernel_stack_top;

    pgd_tmp = (pgd_t *)0x1000;
    pte_low = (pte_t *)0x2000;
    pte_high = (pte_t *)0x3000;

    pgd_tmp[0] = (pgd_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[PGD_INDEX(KERNEL_VADDR_OFFSET)] = (pgd_t)pte_high | PAGE_PRESENT | PAGE_WRITE;

    for (int i = 0; i < 1024; ++i) {
        pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;

        pte_high[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    }

    __asm__ __volatile__ ("mov %0, %%cr3" :: "r" (pgd_tmp));

    // __asm__ __volatile__ ("mov %0, %%cr0" : "=r" (cr0));
    __asm__ __volatile__ ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    __asm__ __volatile__ ("mov %0, %%cr0" :: "r" (cr0));

    gdt_install();

    kernel_stack_top = ((u32)kernel_stack + KERNEL_STACK_SIZE) & 0xFFFFFFF0;

    __asm__ __volatile__ ("mov %0, %%esp\n\t"
                            "xor %%ebp, %%ebp" :: "r" (kernel_stack_top));

    kemain();

    return 0;
}


int kemain()
{

    clear_screen();

/*    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        xprintf("multiboot eax is not equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    } else {
        xprintf("multiboot eax is equal MULTIBOOT_BOOTLOADER_MAGIC.\n");
    }*/

    idt_init();
    timer_init(TIMER_HZ);
    keyboard_init();

    puts(" __  __                                  ___    ____  \n");
    puts("|  \\/  |   ___    _ __ ___     ___      / _ \\  / ___| \n");
    puts("| |\\/| |  / _ \\  | '_ ` _ \\   / _ \\    | | | | \\___ \\ \n");
    puts("| |  | | | (_) | | | | | | | | (_) |   | |_| |  ___) |\n");
    puts("|_|  |_|  \\___/  |_| |_| |_|  \\___/     \\___/  |____/ \n");
    puts("\n=======================================================\n");

    pmm_show(mb_info_ptr);

    pmm_init(mb_info_ptr);
    pmm_test();

    __asm__("sti");

    for (;;)
        ;
    return 0;
}