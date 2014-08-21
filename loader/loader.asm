; this loader is GRUB compatible
; no paging, in protected mode, A20 turned on
global start			; for linder script
[extern kemain]

start:
	jmp loader

MODULE_ALIGN	equ		1 << 0
MEM_MAP			equ 	1 << 1
FLAG			equ		MEM_MAP | MODULE_ALIGN
MAGIC			equ 	0x1BADB002
CHECKSUM		equ 	-(MAGIC + FLAG)

section .text
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
	call kemain
	cli

halt:
	hlt 				; halt when kernel return
	jmp halt

[section .data]
align 4096
stack:
	times STACKSIZE db 00
stack_top:
	dd 0