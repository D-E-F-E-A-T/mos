
mbr.img : mbr.bin
	dd if=mbr.bin of=mbr.img bs=512 count=3 conv=notrunc
mbr.bin : mbr.asm
	nasm mbr.asm -f bin -o mbr.bin

img:
	cat mbr.bin kernel/kernel.bin > mbr.img

clean:
	rm *.o *.bin
