
CC = gcc
CCFLAGS = -ffreestanding -fno-builtin -nostdinc -fno-exceptions -std=c99 -I./kernel/include -I./kernel/drivers/include -I./loader

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = -T kernel.ld
# LDFLAGS = -Ttext 0x1000 --oformat binary

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 

KERNEL_ENTRY_ASM = ./kernel/kernel_entry.asm
KERNEL_ENTRY_O = ./kernel/kernel_entry.o

ISR_WRAPPER_ASM = ./kernel/isr_wrapper.asm
ISR_WRAPPER_O = ./kernel/isr_wrapper.o

BOOT_ASM = ./boot/mbr.asm

C_OBJS	:= 
C_OBJS	+= 	$(patsubst %.c, %.o, $(wildcard ./kernel/drivers/*.c) $(wildcard ./kernel/*.c))
			

mbr.img : mbr.bin loader.bin kernel.bin
	# $(DD) $(DDFLAGS) if=$^ of=$@
	cat $^ > $@

mbr.bin : $(BOOT_ASM)
	$(AS) $< -f bin -o $@

loader.bin : ./loader/loader.o ./loader/pm.o
	ld -T loader.ld -o loader.bin ./loader/pm.o
	dd if=/dev/zero bs=$$((512 - `stat -c "%s" loader.bin`)) count=1 >> loader.bin

./loader/pm.o : ./loader/pm.asm
	$(AS) $< -f elf -o $@
	
kernel.bin : $(KERNEL_ENTRY_O) $(ISR_WRAPPER_O) $(C_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $^


$(KERNEL_ENTRY_O) : $(KERNEL_ENTRY_ASM)
	$(AS) $< -f elf -o $@

$(ISR_WRAPPER_O) : $(ISR_WRAPPER_ASM)
	$(AS) $< -f elf -o $@

.c.o : 
	$(CC) $(CCFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete
