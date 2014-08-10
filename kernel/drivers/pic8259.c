#include <pic8259.h>

void pic8259_init(int _master_index, int _slave_index)
{
	// u8 master_mask, slave_mask;
	// master_mask		= inportb(PIC_MASTER_DATA_PORT);
	// slave_mask		= inportb(PIC_MASTER_DATA_PORT);

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

	// outportb(PIC_MASTER_DATA_PORT, master_mask);
	// outportb(PIC_MASTER_DATA_PORT, slave_mask);

	// Mask/Disable all
	outportb(PIC_MASTER_DATA_PORT, 0xff);
	outportb(PIC_SLAVE_DATA_PORT, 0xff);
}

void _send_eoi(u8 irqno)
{
	if(irqno >= 8)
		outportb(PIC_SLAVE_COMMAND_PORT, PIC_EOI);
 
	outportb(PIC_MASTER_COMMAND_PORT, PIC_EOI);
}


void _disable_irq(u8 index) {
    u16 port;
    u8 value;
 
    if (index < 8) {
        port = PIC_MASTER_DATA_PORT;
    } else {
        port = PIC_SLAVE_DATA_PORT;
        index -= 8;
    }
    value = inportb(port) | (1 << index);
    outportb(port, value);        
}
 
void _enable_irq(u8 index) {
	
    u16 port;
    u8 value;
 
    if (index < 8) {
        port = PIC_MASTER_DATA_PORT;
    } else {
        port = PIC_SLAVE_DATA_PORT;
        index -= 8;
    }
    value = inportb(port) & ~(1 << index);
    outportb(port, value);        
}

