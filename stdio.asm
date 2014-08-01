; DX = string src
print_string:

	mov ah, 0xE  		; print char 
	loop_label:

		mov bx, dx
		mov al, [bx]
		cmp al, 0
		je _null_terminate

		; print al
		mov bh, 0 		; page number
		mov bl, 0x3B 		; 1110 Background color, 100 charactor color, 7th bit sharp
		int 0x10

		inc dx
		jmp loop_label

	_null_terminate:

	ret


; DX: hex value going to print
print_hex:
	
	mov ah, dh
	
	int 10h
	ret


[bits 32]
VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x1F

; Print null-terminate string by copy data to video DMA
; EBX be the source of string
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY

	print_loop:
		mov al, [ebx]				; move the char value to AL 
		mov ah, WHITE_ON_BLACK 		; move char attributes to AH

		cmp al, 0
		je print_string_done		; end loop if null reach

		mov [edx], ax				; move to video memory

		inc ebx 				; move to next charactor and next video display slot
		add edx, 2

	jmp print_loop 				; check next charactor of source string

print_string_done:
	popa
	ret

; Hex	Binary	Color
; 0	0000	Black	 
; 1	0001	Blue	
; 2	0010	Green	
; 3	0011	Cyan	
; 4	0100	Red	
; 5	0101	Magenta	
; 6	0110	Brown	
; 7	0111	Light Gray	
; 8	1000	Dark Gray	
; 9	1001	Light Blue	
; A	1010	Light Green	
; B	1011	Light Cyan	
; C	1100	Light Red	
; D	1101	Light Magenta	
; E	1110	Yellow	
; F	1111	White

clear_screen:
	mov ah, 6	; function 0x6
	mov al, 0 	; how many lines to clear
	mov ch, 0 	; top, left
	mov cl, 0 	
	mov dh, 24	; bottom, right
	mov dl, 79 	
	mov bh, 0x2C	; Background color Light Gray, Foreground color Light Red
	int 10h
	ret