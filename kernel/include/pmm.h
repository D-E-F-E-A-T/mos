#ifndef PMM_H
#define PMM_H

#include <header/multiboot.h>
#include <int.h>
#include <printf.h>

/**
 * Physical memory manager
 * Used after multiboot.
 */

/*void init_bitmap(multiboot_info_t* mb_info);*/

#define FRAME_SIZE (4096)

/* 128K pages */
#define MAX_FRAME_NUMBER (0x20000)

static u32 pmm_free_frames[MAX_FRAME_NUMBER + 1];
static u32 pmm_free_frame_count;

/**
 * The location of kernel when it loaded into memory,
 * provided in linker script PROVIDE( kern_start = . )
 */
extern u32 kern_start[];
extern u32 kern_end[];

void pmm_init(multiboot_info_t* mb_info);

void pmm_show(multiboot_info_t* mb_info);

/**
 * alloc one page of physical memory.
 * @return [description]
 */
u32 pmm_frame_alloc();

/**
 * put a page to free memory pool.
 * @param  page [description]
 */
void pmm_frame_free(u32 page);

/**
 * Align to 4K, 
 * @param  value [description]
 * @return       [description]
 */
u32 ceil4096(u32 value);

void pmm_test();

#endif