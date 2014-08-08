[bits 32]
extern _int_dispatch

%macro ExHandler 1
global _isr%1_wrapper
_isr%1_wrapper:
	push 0
	push %1

	jmp Exception
%endmacro


%macro ExHandlerwithError 1
global _isr%1_wrapper
_isr%1_wrapper:
	push %1

	jmp Exception
%endmacro


%macro IrqHandler 1
global _isr%1_wrapper_irq
_isr%1_wrapper_irq:
	push %1

	call _int_dispatch

	iret
%endmacro


ExHandler 1
ExHandler 2
ExHandler 3
ExHandler 4
ExHandler 5


Exception:

	add esp, 8
	iret

nop
