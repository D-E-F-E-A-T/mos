#include <idt.h>


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


	for (int i = 0; i < 256; ++i)
		isr_setup(i, (void *)int_dispatch, IDT_CODE_SELECTOR, 0x8e);

	// IRQ Mapping
	pic8259_init(USER_DEFINE_ISR, USER_DEFINE_ISR + 8);


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


int int_dispatch(u32 int_no)
{
	xprintf("There is something interrupted\n");
	switch (int_no) {
		case 3:
			_isr3();
			break;
		default:
			;
	}
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
	__asm__ __volatile__("xchg %bx, %bx");	
	puts("\n in _isr3\n");
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


void _isr32_irq0() 
{
	while(1);
}

void _isr33_irq1() 
{
	while(1);
}

void _isr34_irq2() 
{
	while(1);
}

void _isr35_irq3() 
{
	xprintf("this is interrupt %d\n", 35);
	while(1);
}

void _isr36_irq4() 
{
	xprintf("this is interrupt %d\n", 36);
	while(1);
}

void _isr37_irq5() 
{
	xprintf("this is interrupt %d\n", 37);
	while(1);
}

void _isr38_irq6() 
{
	while(1);
}

void _isr39_irq7() 
{
	while(1);
}

void _isr40_irq8() 
{
	while(1);
}

void _isr41_irq9() 
{
	while(1);
}

void _isr42_irq10() 
{
	while(1);
}

void _isr43_irq11() 
{
	while(1);
}

void _isr44_irq12() 
{
	while(1);
}

void _isr45_irq13() 
{
	while(1);
}

void _isr46_irq14() 
{
	while(1);
}

void _isr47_irq15() 
{
	while(1);
}
