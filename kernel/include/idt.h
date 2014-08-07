#ifndef IDT_H
#define IDT_H

#include <int.h>
#include <screen.h>
#include <kernel.h>
#include <pic8259.h>

#define IDT_CODE_SELECTOR	(0x08)
#define USER_DEFINE_ISR		(0x20)

typedef struct 
{
	u16 offset_low;		// offset 0-15
	u16 segment_selector;
	u8	reserved;		// 0
	u8	attr;
	u16 offset_high;		// offset 16-31		
} __attribute__((packed)) IDT_ENTRY;

void idtr_setup();

void isr_setup(u8 idt_index, void *callback, u16 selector, u8 attribute);

void _isr0();
void _isr1();
void _isr2();
void _isr3();
void _isr4();
void _isr5();
void _isr6();
void _isr7();
void _isr8();
void _isr9();
void _isr10();
void _isr11();
void _isr12();
void _isr13();
void _isr14();
void _isr15();
void _isr16();

void _isr32_irq0();
void _isr33_irq1();
void _isr34_irq2();
void _isr35_irq3();
void _isr36_irq4();
void _isr37_irq5();
void _isr38_irq6();
void _isr39_irq7();
void _isr40_irq8();
void _isr41_irq9();
void _isr42_irq10();
void _isr43_irq11();
void _isr44_irq12();
void _isr45_irq13();
void _isr46_irq14();
void _isr47_irq15();

#endif