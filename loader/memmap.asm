MEMMAP_ENTRY_COUNT		equ 0x500
MEMMAP_ENTRY_BASE		equ 0x502

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
read_memory_map:
	; first int 15h
	; mov es, 0 						; es:di = destination
	mov di, MEMMAP_ENTRY_BASE	

	xor ebx, ebx
	mov edx, 0x534D4150				; magic edx = 'SMAP'

	mov eax, 0x0000E820				; 
	mov ecx, 24
	int 15h

	jnc _error						; CF should be clear
	mov edx, 0x534D4150
	cmp eax, edx					; EAX should be 0x534D4150
	jnz _error
	test ebx, ebx					; EBX should not be 0
	jz _error

	; EBX not be zero and used for next query.
	; CL will contain the number of bytes actually stored at ES:DI (probably 20)

	xor eax, eax
	mov [MEMMAP_ENTRY_COUNT], eax 		; count value initial 0
	_loop:
		mov eax, [MEMMAP_ENTRY_COUNT]	; add one to count the total entry number.
		inc eax
		mov [MEMMAP_ENTRY_COUNT], eax

		add di, ENTRY_SIZE				; next memory mapping entry 
		mov eax, 0x0000E820
		mov ecx, 24
		int 15h

		test ebx, ebx
		jnz _loop
		jmp _end_query


	_error:
		mov eax, 0xFFFFFFFF
		mov [MEMMAP_ENTRY_BASE], eax

	_end_query:
		ret