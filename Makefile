
CC = gcc
CCFLAGS = -ffreestanding -fno-builtin -nostdinc -fno-exceptions -I./kernel/include

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 


KERNEL_ENTRY_O = ./kernel/kernel_entry.o

# HEADERS	:=
# HEADERS += 	$(wildcard ./kernel/*.h) \
# 		$(wildcard ./kernel/drivers/*.h)

C_SOURCES	= $(wildcard ./kernel/*.c) \
 		$(wildcard ./kernel/drivers/*.c)

C_OBJS	:= 
C_OBJS	+= 	$(patsubst %.c, %.o, $(C_SOURCES))

# boot sector rules

mbr.img : mbr.bin kernel.bin
	# $(DD) $(DDFLAGS) if=$^ of=$@
	cat $^ > $@

mbr.bin : mbr.asm
	$(AS) $< -f bin -o $@

kernel.bin : $(KERNEL_ENTRY_O) $(C_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(C_OBJS) : $(C_SOURCES)
	$(CC) $(CCFLAGS) -e _kemain -c $^

$(KERNEL_ENTRY_O) : ./kernel/kernel_entry.asm
	$(AS) $< -f elf -o $@

# kernel rules
# # 

.PHONY: clean
clean:
	rm -Rf  *.o *.bin
	rm mbr.img
