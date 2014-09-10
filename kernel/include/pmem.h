#ifndef PMEM_H
#define PMEM_H

#include <header/multiboot.h>
#include <int.h>

/**
 * Physical memory manager
 * Used after multiboot.
 */

void init_bitmap(multiboot_info_t* mb_info);

/**
 * according the physical memory management algorithm
 * to allocate free memory.
 * @param  size [description]
 * @return      [description]
 */
u32 palloc(u32 size);

/**
 * [pfree description]
 * @param  base [description]
 * @param  size [description]
 * @return      [description]
 */
u32 pfree(u32* base, u32 size);

#endif