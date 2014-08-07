
CC = gcc
CCFLAGS = -ffreestanding -fno-builtin -nostdinc -fno-exceptions -std=c99 -I./kernel/include

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 


KERNEL_ENTRY_O = ./kernel/kernel_entry.o


SOURCES	:= 
SOURCES += $(wildcard ./kernel/drivers/*.c) $(wildcard ./kernel/*.c) 

C_OBJS	:= 
C_OBJS	+= 	$(patsubst %.c, %.o, $(wildcard ./kernel/drivers/*.c) $(wildcard ./kernel/*.c))
			

# boot sector rules

mbr.img : mbr.bin kernel.bin
	# $(DD) $(DDFLAGS) if=$^ of=$@
	cat $^ > $@

mbr.bin : mbr.asm gdt.asm stdio.asm load_sector.asm 
	$(AS) $< -f bin -o $@


kernel.bin : $(KERNEL_ENTRY_O) $(C_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $^


$(KERNEL_ENTRY_O) : ./kernel/kernel_entry.asm
	$(AS) $< -f elf -o $@

.c.o : 
	$(CC) $(CCFLAGS) -o $@ -c $<



.PHONY: clean
clean:
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete