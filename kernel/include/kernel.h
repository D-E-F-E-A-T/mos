#ifndef KERNEL_H
#define KERNEL_H

#include <screen.h>
#include <int.h>
#include <string.h>
#include <idt.h>
#include <timer.h>
#include <datetime.h>
#include <printf.h>
#include <header/multiboot.h>
#include <pmm.h>
#include <vmm.h>
#include <gdt.h>
// #include <descriptor.h>

__attribute__((section(".init.data"))) pgd_t *pgd_tmp;
/* map 4M VM start form 0 to 0M PM, used in paging switch on and init code still running. */
__attribute__((section(".init.data"))) pte_t *pte_low;
/* map 4M VM start from 3G to 0M PM */
__attribute__((section(".init.data"))) pte_t *pte_high;


int kemain();

/* 16K kernel stack */
#define KERNEL_STACK_SIZE	(1024 * 16)
u32 kernel_stack[KERNEL_STACK_SIZE];


#endif