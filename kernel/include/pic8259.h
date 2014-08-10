#ifndef PIC8259_H
#define PIC8259_H

#include <port.h>

/*
	in/out these ports for programming of 8259.
*/
#define PIC_MASTER_PORT				(0x20)
#define PIC_SLAVE_PORT				(0xA0)
#define PIC_MASTER_COMMAND_PORT		(PIC_MASTER_PORT)
#define PIC_SLAVE_COMMAND_PORT		(PIC_SLAVE_PORT)
#define PIC_MASTER_DATA_PORT		(PIC_MASTER_COMMAND_PORT + 1)
#define PIC_SLAVE_DATA_PORT			(PIC_SLAVE_COMMAND_PORT + 1)


#define ICW1_ICW4					(0x01)		// 
#define ICW1_SINGLE					(0x02)
#define ICW1_INTERVAL_4				(0x04)		// not use in 8086
#define ICW1_LEVEL					(0x08)		// triggered at level or (edge)
#define ICW1_INIT					(0x10)		// init required

#define ICW4_8086					(0x01)		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO					(0x02)		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE				(0x08)		/* Buffered mode/slave */
#define ICW4_BUF_MASTER				(0x0C)		/* Buffered mode/master */
#define ICW4_SFNM					(0x10)		/* Special fully nested (not) */

#define PIC_EOI						(0x20)		/* End-of-interrupt command code */
 

void pic8259_init(int _master_index, int _slave_index);
void _send_eoi(u8 irqno);

void _enable_irq(u8 index);
void _disable_irq(u8 index);

#endif

