[bits 32]
extern _exception_dispatch, _irq_dispatch

%macro exp 1
	global exp%1_wrapper
	push 0
	push %1
	jmp _exp_wrapper

%endmacro



%macro exp_with_error 1
	global exp%1_wrapper
	push %1
	jmp _exp_wrapper

%endmacro


%macro irq 1
	global irq%1_wrapper
	push %1
	jmp _irq_wrapper

%endmacro


exp 0
exp 1
exp 2
exp 3
exp 4
exp 5
exp 6
exp 7
exp_with_error 8
exp 9
exp_with_error 10
exp_with_error 11
exp_with_error 12
exp_with_error 13
exp_with_error 14
exp 15
exp 16

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

_exp_wrapper:
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
	call _exception_dispatch

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
