; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_strcmp.s                                        :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/06 11:47:35 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:22:51 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	int strcmp(const char *s1, const char *s2);
;	rdi contains `s1`
;	rsi contains `s2`
;
;	flags set by PCMPISTRI
;	CFlag – Reset if IntRes2 is equal to zero, set otherwise
;	ZFlag – Set if any byte/word of xmm2/mem128 is null, reset otherwise
;	SFlag – Set if any byte/word of xmm1 is null, reset otherwise
;	OFlag –IntRes2[0]

section .text

global _ft_strcmp
_ft_strcmp:
	mov							rax, -16

.ft_strcmp_loop:
	lea							rax, [rax + 16]

	movdqu						xmm0, [rdi + rax]				; move 16 bytes of s1 to xmm0

	pcmpistri					xmm0, [rsi + rax], 00011000b	; compare 16 bytes,
																; ....00b = as unsigned bytes
																; ..10..b = mode: "equal each" (= string compare)
																; 01....b = negative polarity (invert each bit of IntRes1 and set to IntRes2)
	ja							.ft_strcmp_loop					; jump if (CF=0 && ZF=0) (loops)
	jc							.found_difference				; jump if (CF=1)
	xor							rax, rax						; if here, no difference was found
	ret

;	index of "found" difference in the 16 bytes will be in rcx
;	so if we add that to value already in rax we get index in string
;	r8 and r9 are "scratch registers" and do not have to be restored
.found_difference:
	add							rax, rcx						; rcx contains position of first "different" byte
	movzx						r9, byte [rsi + rax]			; move zero extended byte to r9
	movzx						rax, byte [rdi + rax]			; move zero extended byte to r8
	sub							rax, r9							; subtract s1[byte]-s2[byte]
	ret

; first try as single byte version
;
; global _ft_strcmp
; _ft_strcmp:
; 	push						rbp								; push value of rbp to stack
; 	mov							rbp, rsp						; reset base of stack to top of stack (creates a stack frame)
; 	push						r8								; push r8 to stack to save original value
; 	push						r9								; push r9 to stack to save original value
; 	mov							r8, 0							; set r8 to 0
; 	mov							r9, 0							; set r9 to 0
; 	mov							rax, 0							; set rax to 0, to be used as counter
; .strcmp_loop:
; 	mov							r8b, byte [rdi + rax]			; store byte of s1
; 	mov							r9b, byte [rsi + rax]			; store byte of s2
; 	sub							r8, r9							; subtract and save result in r8
; 	jnz							.strcmp_ret						; if the result is not zero, it's not equal so we return
; 																; this also catches it if one but not the other to be at end of line
; 																; if the result was zero, we check if r9 is zero because then they were both zero
; 	cmp							r9, 0							; and we reached end of line for both, otherwise they were just equal chars
; 	jz							.strcmp_ret						; and we do nothing
; 	inc							rax								; increment index
; 	jmp							.strcmp_loop					; jump short if zero
; .strcmp_ret:
; 	mov							rax, r8							; set r8 as return value (result of subtraction)
; 	pop							r9								; pop original value of r9 back
; 	pop							r8								; pop original value of r8 back
; 	pop							rbp								; pop original value of rbp back
; 	ret															; return
