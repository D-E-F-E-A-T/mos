#include <idt.h>


void idtr_setup()
{
	/*
		for testing
	*/
	__asm__ __volatile__("xchg %bx, %bx");

	


	gdtr.base = 0x8000;
	GATE_DESCRIPTOR *desc = gdtr.base;

	u32 func_offset = (u32)div0_exp;
	desc[0].offset0 = func_offset & 0xffff;		//	div 0 
	desc[0].offset1 = (func_offset >> 16) & 0xffff;
	desc[0].segment_selector = 0x8;	
	desc[0].attr = 0x8e;

	gdtr.limit = (256 * sizeof(GATE_DESCRIPTOR)) - 1;

	__asm__ __volatile__ ("lidt %0": "=m" (gdtr));
}

void div0_exp()
{
	puts("\n -------- div 0 Exception!!! -----------\n");
	while(1);
}