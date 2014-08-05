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
		dw 0x0 			; Base (0 - 15)
		db 0x0 			; Base (16 - 23)
		db 10010010b 	; 1st flag and type flag
		db 11001111b 	; 2nd flag and Limit (16 - 19)
		db 0x0 			; Base (24 - 31)


gdt_end:

global_descriptor:
	dw 	gdt_end - gdt_start - 1 	; size of GDT 
	dd 	gdt_start 					; GDT address

; Constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
