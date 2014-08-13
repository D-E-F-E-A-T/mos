
CC = gcc
CCFLAGS := -ffreestanding -fno-builtin -nostdinc -fno-exceptions -std=c99 \
	-I./kernel/include -I./kernel/drivers/include -I./loader

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = 

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 

KERNEL_ENTRY_ASM = ./kernel/kernel_entry.asm
KERNEL_ENTRY_O = ./kernel/kernel_entry.o

ISR_WRAPPER_ASM = ./kernel/isr_wrapper.asm
ISR_WRAPPER_O = ./kernel/isr_wrapper.o

BOOT_ASM = ./boot/mbr.asm

LOADER_ASM 	= $(wildcard ./loader/*.asm)
LOADER_O 	= $(patsubst %.asm, %.o, $(LOADER_ASM))

C_OBJS	:= 
C_OBJS	+= 	$(patsubst %.c, %.o, $(wildcard ./kernel/drivers/*.c) $(wildcard ./kernel/*.c))
			

mbr.img : mbr.bin loader.bin kernel.bin
	cat $^ > $@

mbr.bin : $(BOOT_ASM)
	$(AS) $< -f bin -o $@

loader.bin : ./loader/loader.o $(LOADER_O)
	$(LD) -T loader.ld -o loader.bin $(LOADER_O)
	dd if=/dev/zero bs=$$((512 - `stat -c "%s" loader.bin`)) count=1 >> loader.bin
	
kernel.bin : $(KERNEL_ENTRY_O) $(ISR_WRAPPER_O) $(C_OBJS) 
	$(LD) -T kernel.ld -o $@ $^

%.o : %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

%.o : %.asm
	$(AS) $< -f elf -o $@

.PHONY: clean
clean:
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete
