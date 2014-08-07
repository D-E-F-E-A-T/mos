#include <idt.h>
#include <kernel.h>

IDTR 		idtr;
IDT_ENTRY	*IDT;


void idtr_setup()
{
	/*
		for testing
	*/
	__asm__ __volatile__("xchg %bx, %bx");


	idtr.base = 0x3FF0000;
	IDT  = (IDT_ENTRY *)idtr.base;

	isr_setup(0, _isr0, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(1, _isr1, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(2, _isr2, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(3, _isr3, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(4, _isr4, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(5, _isr5, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(6, _isr6, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(7, _isr7, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(8, _isr8, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(9, _isr9, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(10, _isr10, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(11, _isr11, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(12, _isr12, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(13, _isr13, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(14, _isr14, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(15, _isr15, IDT_CODE_SELECTOR, 0x8e);
	isr_setup(16, _isr16, IDT_CODE_SELECTOR, 0x8e);


	idtr.limit = (256 * sizeof(IDT_ENTRY)) - 1;
	
	__asm__ __volatile__ ("lidt %0": "=m" (idtr));
}


void isr_setup(u8 idt_index, void *callback, u16 selector, u8 attribute)
{

	IDT[idt_index].offset_low = (u32)callback & 0xffff;		//	div 0 
	IDT[idt_index].offset_high = ((u32)callback >> 16) & 0xffff;
	IDT[idt_index].segment_selector = selector;	
	IDT[idt_index].attr = attribute;
}


void _isr0() 
{
	puts("\n DIV 0 in _isr0\n");
	while(1);
}

void _isr1() 
{
	while(1);
}

void _isr2() 
{
	while(1);
}

void _isr3() 
{
	while(1);
}

void _isr4() 
{
	while(1);
}

void _isr5() 
{
	while(1);
}

void _isr6() 
{
	while(1);
}

void _isr7() 
{
	while(1);
}

void _isr8() 
{
	while(1);
}

void _isr9() 
{
	while(1);
}

void _isr10() 
{
	while(1);
}

void _isr11() 
{
	while(1);
}

void _isr12() 
{
	while(1);
}

void _isr13() 
{
	while(1);
}

void _isr14() 
{
	while(1);
}

void _isr15() 
{
	while(1);
}

void _isr16() 
{
	while(1);
}
