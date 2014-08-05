#include <idt.h>


void idtr_setup()
{
	/*
		for testing
	*/

	GATE_DESCRIPTOR div0;
	u32 func_offset = (u32)div0_exp;
	div0.offset0 = func_offset & 0xffff;
	div0.offset1 = (func_offset >> 16) & 0xffff;
	div0.segment_selector = 0x8;
	div0.attr = 0x8e;


	gdtr.base = 0x90000;
	gdtr.limit = (256 * sizeof(GATE_DESCRIPTOR)) - 1;

	__asm__ __volatile__ ("lidt %0": "=m" (gdtr));
}

void div0_exp()
{
	puts("div 00000\n");
}