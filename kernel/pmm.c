#include <pmm.h>

/**
 * Align to 4K, 
 * @param  value [description]
 * @return       [description]
 */
u32 ceil4096(u32 value)
{
    return (value + 4095) >> 12 << 12;
}

void pmm_init(multiboot_info_t* mb_info)
{
    multiboot_memory_map_t* mmap_entry_start = (multiboot_memory_map_t*)mb_info->mmap_addr;

    multiboot_memory_map_t* mmap_entry_end = (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length);

    u32 kernel_size = (u32)kern_end - (u32)kern_start;

    u32 pstart, pend;

    pmm_free_frame_count = 0;

    // search for a memory block type is 1 and above 1M
    while (mmap_entry_start <= mmap_entry_end) {
        if (mmap_entry_start->type == 1 && mmap_entry_start->addr_low > 0x100000)
            break;

        mmap_entry_start++;
    }

    // put it all into free frames
    kernel_size = ceil4096(kernel_size);
    pend = mmap_entry_start->addr_low + mmap_entry_start->len_low;
}

void pmm_show(multiboot_info_t* mb_info)
{
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

    xprintf("Kernel Memory used:\n");
    xprintf("Kernel Start: %08X, Kernel End: %08X,\n Kernel Length: 0x%08X, %d\n",
            kern_start, kern_end, (u32)kern_end - (u32)kern_start);
}

/**
 * alloc one page of physical memory.
 * @return [description]
 */
u32 pmm_frame_alloc()
{
    return pmm_free_frames[--pmm_free_frame_count];
}

/**
 * put a page to free memory pool.
 * @param  page [description]
 */
void pmm_frame_free(u32 page)
{
    pmm_free_frames[pmm_free_frame_count++] = page;
}