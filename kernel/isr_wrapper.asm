[bits 32]
extern _exception_dispatch, _irq_dispatch


%macro exp 1
	global exp%1_wrapper
	exp%1_wrapper:
		cli
		xchg bx, bx
		push 0
		push %1
		jmp exp_wrapper

%endmacro

%macro exp_with_error 1
	global exp%1_wrapper
	exp%1_wrapper:
		cli
		push %1
		jmp exp_wrapper

%endmacro


%macro irq 1
	global irq%1_wrapper
	irq%1_wrapper:
		cli
		push %1
		jmp irq_wrapper

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

exp_wrapper:
	
	pushad
	push ds
	push es
	push fs
	push gs

	mov eax, esp
	push eax
	call _exception_dispatch
	pop eax

	pop ds
	pop es
	pop fs
	pop gs
	popad
	add esp, 8

	iret

irq_wrapper:
	pushad
	push ds
	push es
	push fs
	push gs

	mov eax, esp
	push eax
	call _irq_dispatch
	pop eax

	pop ds
	pop es
	pop fs
	pop gs
	popad
	add esp, 4

	iret
