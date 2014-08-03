
CC = gcc
CCFLAGS = -ffreestanding 

AS = nasm
# ASFLAGS = 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 

KERNEL_DIR		= ./kernel/
KERNEL_OBJS		= $(wildcard $(KERNEL_DIR)*.o $(DRIVER_DIR)*.o)

# boot sector rules

mbr.img : mbr.bin $(KERNEL_DIR)kernel.bin
	# $(DD) $(DDFLAGS) if=$^ of=$@
	cat $^ > $@

mbr.bin : mbr.asm
	$(AS) $< -f bin -o $@

$(KERNEL_DIR)kernel.bin : $(KERNEL_OBJS)
	make -f $(KERNEL_DIR)Makefile

# kernel rules
# # 

.PHONY: clean
clean:
	rm -f *.o *.bin
	rm mbr.img
	cd kernel && rm -f *.o *.bin
	cd kernel/drivers && rm -f *.o
