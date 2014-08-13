[org 0x7c00]

LOADER_SIZE		equ 0x1 		; how many sector the loader needed.
KERNEL_SIZE		equ 17 + 18 * 1			; 17 for first cylinder and 18 full of second cylinders will be load into memory

_start:
	mov [BOOT_DEVICE], dl
	mov ax, cs
	mov ds, ax
	mov es, ax
	; mov ss, ax

	mov bp, 0x8000
	mov sp, bp

	call load_kernel
	call load_loader 		; load loader.bin into 0x1000

	jmp $

load_kernel:
	mov bx, KERNEL_OFFSET
	mov dh, KERNEL_SIZE
	mov dl, [BOOT_DEVICE]		; read from boot drive (floppy A)
	mov cl, 3 					; read start from sector 3, sector 1 is MBR, sector 2 is loader.
	call disk_load

	ret

load_loader:
	mov bx, LOADER_OFFSET
	mov dh, LOADER_SIZE 					; 1 sector will be read for loader.
	mov dl, [BOOT_DEVICE]		; read from boot drive (floppy A)
	mov cl, 2 					; read start from sector 3, sector 1 is MBR, sector 2 is loader.
	call disk_load

	xchg bx, bx
	call LOADER_OFFSET

	ret

%include "./boot/load_sector.asm"

BOOT_DEVICE:
	db 0
	
DISK_ERROR_MSG:
	db " Disk read error !", 0

	times 510 - ($ - $$) db 0
	dw 0xAA55
