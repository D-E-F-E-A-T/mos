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

	isr_setup(0, (void *)exp0_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(1, (void *)exp1_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(2, (void *)exp2_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(3, (void *)exp3_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(4, (void *)exp4_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(5, (void *)exp5_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(6, (void *)exp6_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(7, (void *)exp7_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(8, (void *)exp8_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(9, (void *)exp9_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(10, (void *)exp10_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(11, (void *)exp11_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(12, (void *)exp12_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(13, (void *)exp13_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(14, (void *)exp14_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(15, (void *)exp15_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(16, (void *)exp16_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);

	isr_setup(IRQ_BASE + 0, (void *)irq0_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 1, (void *)irq1_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 2, (void *)irq2_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 3, (void *)irq3_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 4, (void *)irq4_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 5, (void *)irq5_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 6, (void *)irq6_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 7, (void *)irq7_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 8, (void *)irq8_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 9, (void *)irq9_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 10, (void *)irq10_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 11, (void *)irq11_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 12, (void *)irq12_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 13, (void *)irq13_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 14, (void *)irq14_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);
	isr_setup(IRQ_BASE + 15, (void *)irq15_wrapper, IDT_CODE_SELECTOR, IDT_ENTRY_FLAGS);

	// IRQ Mapping
	pic8259_init(IRQ_BASE, IRQ_BASE + 8);


	idtr.limit = (256 * sizeof(IDT_ENTRY)) - 1;
	
	__asm__ __volatile__ ("lidt %0": "=m" (idtr));
}


void isr_setup(u8 idt_index, void *callback, u16 selector, u8 attribute)
{

	IDT[idt_index].offset_low = (u32)callback & 0xffff;	
	IDT[idt_index].offset_high = ((u32)callback >> 16) & 0xffff;
	IDT[idt_index].segment_selector = selector;	
	IDT[idt_index].attr = attribute;
}

void _exception_dispatch(IDT_EXP_CONTEXT exp_context)
{
	puts("in _exception_dispatch \n");
}


void _irq_dispatch(IDT_IRQ_CONTEXT irq_context)
{
	puts("in _irq_dispatch \n");

}

