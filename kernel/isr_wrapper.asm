[bits 32]
extern _interrupt_dispatch, _irq_dispatch

%macro isr 1
	global isr%1_wrapper
	push 0
	push %1
	jmp _isr_wrapper

%endmarco



%macro isr_with_error 1
	global isr%1_wrapper
	push %1
	jmp _isr_wrapper

%endmarco


%macro irq 1
	global irq%1_wrapper
	push %1
	jmp _irq_wrapper

%endmarco


_isr_wrapper:
	pushad
	push ds 
	push es
	push fs
	push gs

	mov eax, 0x10
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	call _interrupt_dispatch

	pop gs
	pop fs
	pop es
	pop ds

	popad

	iret

_irq_wrapper:
	pushad
	push ds 
	push es
	push fs
	push gs

	mov eax, 0x10
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	call _irq_dispatch

	pop gs
	pop fs
	pop es
	pop ds

	popad

	iret
