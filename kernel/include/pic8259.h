#ifndef PIC8259_H
#define PIC8259_H

#include <port.h>

#define PIC_MASTER_PORT				(0x20)
#define PIC_SLAVE_PORT				(0xA0)
#define PIC_MASTER_COMMAND_PORT		PIC_MASTER_PORT
#define PIC_SLAVE_COMMAND_PORT		PIC_SLAVE_PORT
#define PIC_MASTER_DATA_PORT		(PIC_MASTER_COMMAND_PORT + 1)
#define PIC_SLAVE_DATA_PORT			(PIC_SLAVE_COMMAND_PORT + 1)

#define ICW1_

void pic8259_init();



#endif

