; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
[bits 32]
[section .text]
global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
	mov eax, cr0
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov eax, cr0
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               ; Returns back to the C code!


%macro  CRXFunc 1
global _keGetCR%1, _keSetCR%1
_keGetCR%1:
	mov eax, cr%1
	retn
_keSetCR%1:
	push ebp
	mov ebp,esp
	mov eax, [ebp+8]
	mov cr%1, eax
	leave
	retn
%endmacro

CRXFunc 0
CRXFunc 2
CRXFunc 3