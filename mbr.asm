[org 0x7c00]
KERNEL_OFFSET equ 0x1000

_start:
	mov [BOOT_DEVICE], dl
	mov ax, cs
	mov ds, ax
	mov es, ax
	; mov ss, ax

	mov bp, 0x8000
	mov sp, bp
	
	mov dx, HELLO_MSG		; print 16 bits real mode message
	call print_string

	call load_kernel 		; load kernel.bin into 0x1000

	call switch_to_pm
	
	jmp $

load_kernel:
	mov dx, MSG_KERNEL_LOAD 	; print kernel loading message
	call print_string

	mov bx, KERNEL_OFFSET
	mov dh, 17 + 18 * 1			; 17 for first cylinder and 18 full of second cylinders will be load into memory
	mov dl, [BOOT_DEVICE]		; read from boot drive (floppy A)
	call disk_load

	ret

[bits 16]
switch_to_pm:
	; go into 32 bits Protected mode
	cli
	lgdt [global_descriptor]
	; set A20 for access 32bit address
	in al, 0x92
	or al, 2
	out 0x92, al

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm		; flush pre-fetch instruction pipeline in real mode


%include "stdio.asm"
%include "load_sector.asm"
%include "gdt.asm"

[bits 32]
begin_pm:
	mov ebx, PROTECTED_MESSAGE
	call print_string_pm
	call KERNEL_OFFSET

	jmp $

init_pm:
	mov ax, DATA_SEG 		; old segment in protected mode is meaningless, 
							; change to Data segment defined
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov fs, ax
	mov ss, ax

	mov ebp, 0x90000 		; update stack position at the top of free space
	mov esp, ebp

	call begin_pm

HEX_BUFFER:
	db "0000"

BOOT_DEVICE:
	db 0

MSG_KERNEL_LOAD:
	db "Kernel Loading...", 0
	
DISK_ERROR_MSG db " Disk read error !", 0

HELLO_MSG:
	db "Hello World ! This is 16 bits real mode.", 0

PROTECTED_MESSAGE:
	db "This is 32 bits protected mode.", 0

GOODBYE_MSG:
	db "Bye bye ~", 0
	times 510 - ($ - $$) db 0
	dw 0xAA55

	; second sector
	; times 256 dw "AB"
	; times 256 dw "CC"
