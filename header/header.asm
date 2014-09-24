; this loader is GRUB compatible
; no paging, in protected mode, A20 turned on
global start			; for linder script
[extern keinit]

start:
	jmp loader

MODULE_ALIGN	equ		1 << 0
MEM_MAP			equ 	1 << 1
FLAG			equ		MEM_MAP | MODULE_ALIGN
MAGIC			equ 	0x1BADB002
CHECKSUM		equ 	-(MAGIC + FLAG)

section .init.text
align 4

multiboot_header:
	dd MAGIC 			; multiboot header magic
	dd FLAG
	dd CHECKSUM

; stack space for store boot infomation
STACKSIZE	equ 0x4000		; 16K

loader:
	mov esp, stack_top

	finit
	push eax
	push ebx
	call keinit
	cli

	; debug point when halt
	xchg bx, bx

halt:
	hlt 				; halt when kernel return
	jmp halt



global gdt_setup

; code segment and data segment definition
gdt_start:

	gdt_null:
		dd 0x0
		dd 0x0

	gdt_code:
		; code base = 0x0, limit = 0xFFFFF
		; 1st flag: (present) 1, (privilege) 00, (descriptor type) 1 -> 1001b
		; type flag: (code) 1, (conforming) 0, (readable) 1, (accessed) 0 -> 1010b
		; 2nd flag: (granularity) 1, (32bit default) 1, (64bit segment) 0, (AVL) 0 -> 1100b

		dw 0xFFFF 		; Limit (0 - 15)
		dw 0x0 			; Base (0 - 15)
		db 0x0 			; Base (16 - 23)
		db 10011010b 	; 1st flag and type flag
		db 11001111b 	; 2nd flag and Limit (16 - 19)
		db 0x0 			; Base (24 - 31)

	gdt_data:
		; same as code segment but type flag
		; type flag: (code) 0, (expand down) 0, (writable) 1, (accessed) 0 -> 0010b
		dw 0xFFFF 		; Limit (0 - 15)
		dw 0x0			; Base (0 - 15)
		db 0x0 			; Base (16 - 23)
		db 10010010b 	; 1st flag and type flag
		db 11001111b 	; 2nd flag and Limit (16 - 19)
		db 0x0			; Base (24 - 31)


gdt_end:

global_descriptor:
	dw 	gdt_end - gdt_start - 1 	; size of GDT 
	dd 	gdt_start 					; GDT address

; Constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


gdt_setup:
	cli
	lgdt [global_descriptor]

	jmp CODE_SEG:set_cs
set_cs:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov gs, ax
	mov fs, ax
	ret


[section .init.data]
align 4096
stack:
	times STACKSIZE db 00
stack_top:
	dd 0