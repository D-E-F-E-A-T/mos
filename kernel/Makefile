
CC = gcc
CCFLAGS = -ffreestanding 

AS = nasm
ASFLAGS = 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

# kernel.bin : kernel_entry.o kernel.o
# 	$(LD) $(LDFLAGS) -o $@ $^

# kernel_entry.o : kernel_entry.asm
# 	$(AS) $< -f elf -o $@

# kernel.o : kernel.c
# 	$(CC) $(CCFLAGS) -e main -c $< -o $@

	
# dis:
# 	ndisasm -b32 kernel.bin



DRIVER_DIR = ./drivers/
KERNEL_DIR = ./


KERNEL_SRC		:= 
KERNEL_SRC		+= $(wildcard $(KERNEL_DIR)*.c) $(wildcard $(DRIVER_DIR)*.c)

KERNEL_OBJS		= $(patsubst %.c, %.o, $(KERNEL_SRC))
KERNEL_HEADER	= $(wildcard $(KERNEL_DIR)*.h $(DRIVER_DIR)*.h)

$(KERNEL_DIR)kernel.bin : $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(KERNEL_DIR)kernel_entry.o : $(KERNEL_DIR)kernel_entry.asm
	$(AS) $< -f elf -o $@

$(KERNEL_OBJS) : $(KERNEL_SRC)
	$(CC) $(CCFLAGS) -e main -c $^ 

clean:
	rm *.o *.bin