; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_strcpy.s                                        :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/08 18:02:28 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:22:49 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;   char *strcpy(char * dst, const char * src);
;	rdi contains `dst`
;	rsi contains `src`

section .text

global _ft_strcpy
_ft_strcpy:
	mov							rax, 0							; set counter to 0
.strcpy_loop:
	cmp byte 					[rsi + rax], 0					; compare char[rax] with '\0'
	mov							cl, [rsi + rax]					; store byte (char) in temp register (counter cl = 1 byte)
	mov							[rdi + rax], cl					; copy byte in destination str
	lea							rax, [rax + 1]					; increment counter, lea does not affect flags (add/inc does!)
	jne							.strcpy_loop					; if compare from top is not false jump back
	lea							rax, [rdi]						; set dst ptr as return value
	ret
