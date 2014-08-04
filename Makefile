
CC = gcc
CCFLAGS = -ffreestanding -fno-stack-protector

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

DD = dd
DDFLAGS = bs=512 count=3 conv=notrunc 


KERNEL_ENTRY_O = ./kernel/kernel_entry.o

HEADERS	:=
HEADERS += 	$(wildcard ./kernel/*.h) \
		$(wildcard ./kernel/drivers/*.h)

C_SOURCES	= $(patsubst %.h, %.c, $(HEADERS))

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
	$(CC) $(CCFLAGS) -e main -c $^

$(KERNEL_ENTRY_O) : ./kernel/kernel_entry.asm
	$(AS) $< -f elf -o $@

# kernel rules
# # 

.PHONY: clean
clean:
	rm -Rf  *.o *.bin
	rm mbr.img
