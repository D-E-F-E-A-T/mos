extern void switch_to_pm();
extern void read_memory_map();

#include <loader/multiboot.h>

// multiboot_info_t boot_info;
// multiboot_info_t* pboot_info = &boot_info;

void _loader()
{
    read_memory_map();
    switch_to_pm();
}
