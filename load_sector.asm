
; AL count of sector will be read
; CL sector started
; disk_load:
; 	push dx ; Store DX on stack so later we can recall
; 			; how many sectors were request to be read ,
; 			; even if it is altered in the meantime
; 	mov ah , 0x02 	; BIOS read sector function
; 	mov al , dh 	; Read DH sectors
; 	mov ch , 0x00 	; Select cylinder 0
; 	mov dh , 0x00 	; Select head 0
; 	mov cl , 0x02 	; Start reading from second sector ( i.e.
; 					; after the boot sector )
; 	int 0x13  		; BIOS interrupt

; 	jc disk_error 	; Jump if error ( i.e. carry flag set )
; 	pop dx 			; Restore DX from the stack
; 	cmp dh , al 	; if AL ( sectors read ) != DH ( sectors expected )
; 	jne disk_error 	; display error message
; 	ret

; 	disk_error :
; 		mov bx , DISK_ERROR_MSG
; 		call print_string
; 		jmp $

; 	; Variables
; 	DISK_ERROR_MSG db " Disk read error !", 0



; DH: sectors will be read
; DL: 
disk_load:
	push dx


	mov ah, 0x2			; read function of int 13h
	
	; drive 0 (dl), cylinder 0, head 0 (dh), start form sector dh, read al sectors.
	mov al, dh 			; read dh sectors
	mov dh, 0 			; head 0
	mov ch, 0 			; Cylinder 0
	mov cl, 2 			; start form sector 2

	
	int 0x13
	jc disk_read_error
	pop dx
	cmp al, dh
	jne disk_read_error
	
	ret

disk_read_error:
	push DISK_ERROR_MSG
	call print_string
	jmp $