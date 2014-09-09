# Momo OS


## A mini x86 kernel for fun.

#### Log

[PIT Frequency too high in Bochs Problem.](http://forum.osdev.org/viewtopic.php?f=1&t=27574)

~~No memory management or well linking ? just place keyboard mapping in a fixed memory block which defined at keyboard.h.~~

Floppy reading just let cylinder 0 - 79 like a flat mode, no need to set cylinder and just let it be 0. Sector value will calculate automatically.

If using STARTUP in linker script then startup object file should not occur in argument list, otherwise redefinition error will occur.

~~#### Booting

* [MBR.bin](./boot/mbr.asm) loaded at 0x7C00, it just load loader.bin and kernel.bin into memory by using int 13h
* [Loader.bin](./loader/loader.c) loaded at 0x1000, loader collects computer infomation and stroe into somewhere, then switch to 32 bit protected mode.
* [Kernel.bin](./kernel/kernel.c) loaded at 0x2000, kennel will initialize the IDT and IRQ to handle requests. Then it should perpare the API of mm, fs, io, tasks ...~~


#### Hide Booting detail using GRUB2
* sudo kpartx -av c.img, mount one of patition
* sudo mount /dev/mapper/loop1p1 /mnt/img, mount the patition
* copy the kernel into patition space ...
* boot OS using harddisk image.
* steps in [内核引导的捷径(grub2安装到U盘,虚拟镜像等方法)](http://www.cnblogs.com/crazyyer/p/3658358.html)
* do not mkfs in virtualbox shared folder, it will got problem.
