#ifndef KERNEL_H
#define KERNEL_H

#include <screen.h>
#include <int.h>
#include <string.h>
#include <idt.h>
#include <timer.h>
#include <datetime.h>
#include <printf.h>
#include <mm.h>
#include <loader/multiboot.h>
// #include <descriptor.h>

typedef struct
    {
    u16 limit;
    u32 base;
} __attribute__((packed)) IDTR;

#endif