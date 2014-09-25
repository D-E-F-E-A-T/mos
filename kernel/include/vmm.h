#ifndef VMM_H
#define VMM_H

#include <int.h>

/* VA of kernel image when paging switch on */
#define KERNEL_VADDR_OFFSET (0xC0000000)

#define PAGE_SIZE (4096)

#define PAGE_PRESENT	(1)
#define PAGE_WRITE		(2)
#define PAGE_PRIV		(4)

typedef u32 pgd_t;
typedef u32 pte_t;



#define PGD_INDEX(x) ((x >> 22) & 0x3FF)
#define PTE_INDEX(x) ((x >> 12) & 0x3FF)
#define VA_OFFSET(x) (x & 0xFFF)

void init_pagging();
#endif