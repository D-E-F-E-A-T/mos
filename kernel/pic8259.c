#include <pic8259.h>

void pic8259_init(int _master_index, int _slave_index)
{
	u8 master_mask, slave_mask;
	master_mask		= inportb(PIC_MASTER_DATA_PORT);
	slave_mask		= inportb(PIC_MASTER_DATA_PORT);

	// ICW1
	outportb(PIC_MASTER_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outportb(PIC_SLAVE_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();

	// ICW2
	outportb(PIC_MASTER_DATA_PORT, _master_index);
	io_wait();
	outportb(PIC_SLAVE_DATA_PORT, _slave_index);
	io_wait();

	// ICW3
	outportb(PIC_MASTER_DATA_PORT, 4);
	io_wait();
	outportb(PIC_SLAVE_DATA_PORT, 2);
	io_wait();

	// ICW4
	outportb(PIC_MASTER_DATA_PORT, ICW4_8086);
	io_wait();
	outportb(PIC_SLAVE_DATA_PORT, ICW4_8086);
	io_wait();	

	outportb(PIC_MASTER_DATA_PORT, master_mask);
	outportb(PIC_MASTER_DATA_PORT, slave_mask);
}

// form OSDev
// void PIC_remap(int offset1, int offset2)
// {
// 	unsigned char a1, a2;
 
// 	a1 = inb(PIC1_DATA);                        // save masks
// 	a2 = inb(PIC2_DATA);
 
// 	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
// 	io_wait();
// 	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
// 	io_wait();
// 	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
// 	io_wait();
// 	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
// 	io_wait();
// 	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
// 	io_wait();
// 	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
// 	io_wait();
 
// 	outb(PIC1_DATA, ICW4_8086);
// 	io_wait();
// 	outb(PIC2_DATA, ICW4_8086);
// 	io_wait();
 
// 	outb(PIC1_DATA, a1);   // restore saved masks.
// 	outb(PIC2_DATA, a2);
// }