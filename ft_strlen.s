; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_strlen.s                                        :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/08 18:01:28 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:04 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

section .text

global _ft_strlen
_ft_strlen:
	mov							rax, -16						; Load -16 in return value
	pxor						xmm0, xmm0						; Make sure xmm1 is all zero's
.ft_strlen_loop:
	lea							rax, [rax + 16]
	pcmpistri					xmm0, [rdi + rax], 00001010b	; Commpare xmm0 with xmm1, ------10b = use 128-bit as 16 packed signed bytes
																; ----10--b = comp. mode = "equal each", since xmm1 is all 0 it finds zero's in any place
																; pcmpistri returns the left-most index of an valid comparison in rcx
																; is one of the bytes in second operand are NULL the zero flag is set
	jnz							.ft_strlen_loop
	add							rax, rcx
	ret

; this was the working one I had before going for PCMPISTRI
;_ft_strlen:
;	mov							rax, -1							; set counter to -1 so it can be incremented at top of loop
;.strlen_loop:
;	lea							rax, [rax + 1]					; increment counter (lea does not affect flags like add/inc)
;	cmp byte 					[rdi + rax], 0					; check rdi (str variable) for '\0'
;	jne 						.strlen_loop					; if cmp wasn't '\0' jump back to start of loop
;	ret
