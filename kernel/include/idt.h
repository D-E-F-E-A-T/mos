#ifndef IDT_H
#define IDT_H
#include <int.h>
#include <screen.h>


typedef struct 
{
	u16 limit;
	u32 base;
} __attribute__((packed)) GDTR;


typedef struct 
{
	u16 offset0;		// offset 0-15
	u16 segment_selector;
	u8	reserved;		// 0
	u8	attr;
	u16 offset1;		// offset 16-31		
} __attribute__((packed)) GATE_DESCRIPTOR;


GDTR gdtr;



void div0_exp();

void idtr_setup();

#endif