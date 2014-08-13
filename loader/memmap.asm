MEMMAP_ENTRY_COUNT		equ 0x500
MEMMAP_ENTRY_BASE		equ 0x504

ENTRY_SIZE				equ 24

; Address 			Size 	Name
; 0x0000:0x0000 	1024 bytes 	Interrupt Vector Table
; 0x0040:0x0000 	256 bytes 	BIOS Data Area
; 0x0050:0x0000 	? 	Free memory
; 0x07C0:0x0000 	512 bytes 	Boot sector code
; 0x07E0:0x0000 	? 	Free memory
; 0xA000:0x0000 	64 Kb 	Graphics Video Memory
; 0xB000:0x0000 	32 Kb 	Monochrome Text Video Memory
; 0xB800:0x0000 	32 Kb 	Color Text Video Memory
; 0xC000:0x0000 	256 Kb1 	ROM Code Memory
; 0xFFFF:0x0000 	16 bytes 	More BIOS data

[bits 16]
global read_memory_map

; read memory mapping using BIOS int 15
; store mapping information at 0:0x500 for 32 bit protected mode need.
; ignore ACPI extend
read_memory_map:
	; first int 15h
	; mov es, 0 						; es:di = destination
	pushfd
	pushad

	xor ebp, ebp
	mov di, MEMMAP_ENTRY_BASE	

	xor ebx, ebx
	mov edx, 0x534D4150				; magic edx = 'SMAP'

	mov eax, 0x0000E820				; 
	mov ecx, 24
	int 15h

	jc _error						; CF should be clear
	; mov edx, 0x534D4150
	; cmp eax, edx					; EAX should be 0x534D4150
	; jnz _error
	
	inc ebp

	test ebx, ebx					; EBX is a continuation mark, 0 for no next entry
	jz _end_loop

	; EBX not be zero and used for next query.
	; CL will contain the number of bytes actually stored at ES:DI (probably 20)

	_loop:

		inc ebp							; add one to count the total entry number.

		add di, ENTRY_SIZE				; next memory mapping entry 
		mov eax, 0x0000E820
		mov ecx, 24
		int 15h

		test ebx, ebx 					
		jnz _loop						; 0 of continuation mark, no next entry
		
	_end_loop:
		mov [MEMMAP_ENTRY_COUNT], ebp
		jmp _end_query

	_error:
		mov eax, 0xFFFFFFFF				; set count = -1 if error occur
		mov [MEMMAP_ENTRY_COUNT], eax

	_end_query:
		popad
		popfd
		ret