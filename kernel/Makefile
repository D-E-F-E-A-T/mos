
kernel.bin : kernel_entry.o kernel.o
	ld -o $@ -Ttext 0x1000 --oformat binary $^
kernel_entry.o : kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o : kernel.c
	gcc -g -e main -ffreestanding -c $< -o $@

	
dis:
	ndisasm -b32 kernel.bin

clean:
	rm *.o *.bin
