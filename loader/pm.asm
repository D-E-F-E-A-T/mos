
[bits 16]
global switch_to_pm
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


; %include "./boot/stdio.asm"
%include "./boot/load_sector.asm"
%include "./boot/gdt.asm"

[bits 32]
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

begin_pm:
	call KERNEL_OFFSET

	jmp $