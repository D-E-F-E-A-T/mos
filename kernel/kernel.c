#include <kernel.h>

__attribute__((section(".init.text"))) int keinit(multiboot_info_t* mb_info, u32 mb_magic)
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

    __asm__ __volatile__ ("mov %0, %%cr0" : "=r" (cr0));
    cr0 |= 0x80000000;
    __asm__ __volatile__ ("mov %0, %%cr0" :: "r" (cr0));

    kernel_stack_top = ((u32)kernel_stack + KERNEL_STACK_SIZE) & 0xFFFFFFF0;

    mb_info = (multiboot_info_t *)((u32)mb_info + KERNEL_VADDR_OFFSET);
    kemain(mb_info, mb_magic);

    return 0;
}

/*void gdt_setup()
{

}*/

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

    /*pmm_show(mb_info);

    

    pmm_init(mb_info);
    pmm_test();*/

    __asm__("sti");

    for (;;)
        ;
    return 0;
}