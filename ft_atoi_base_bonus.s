; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_atoi_base_bonus.s                               :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/06 11:51:47 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:53 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	int ft_atoi_base(char *str, char *base);
;	must handle negatives (duh. otherwise ret unsigned)
;	handle signs like atoi
;	ret 0 if:
; 		- str is empty or NULL
;		- base is len 0 or 1 or NULL
;		- str contains chars that are not in base
;		- base contains chars twice
;		- base contains + or -
;		- etc.... ?? <- wtf??
;
;	rdi = str
;	rsi = base

section .text

global _ft_atoi_base
extern _ft_strlen
_ft_atoi_base:
	push						r15								; r15 is callee save
	cmp							rdi, 0							; check rdi for NULL
	je							.ft_atoi_base_err
	cmp							rsi, 0							; check rsi for NULL
	je							.ft_atoi_base_err
	xor							rax, rax						; make sure rax is zero
	mov							rcx, -1							; set counter to -1
.check_base_inc:
	inc							rcx
.check_base_str:
	cmp							byte [rsi + rcx], 43			; 45='-'
	je							.ft_atoi_base_err
	cmp							byte [rsi + rcx], 45			; 43='+'
	je							.ft_atoi_base_err
	cmp							byte [rsi + rcx], 0				; if end of string
	je							.is_base_valid					; jump to strlen_check
	xor							r8, r8							; set r8 to zero
	xor							r9, r9							; set r8 to zero
.check_base_tail:
	cmp							r8, rcx							; if we reach current char, jump back to base_inc
	je							.check_base_inc
	mov							r9b, byte [rsi + r8]			; load byte of rsi to r9b
	cmp							byte [rsi + rcx], r9b			; compare to current char
	je							.ft_atoi_base_err				; if byte and current byte are equal, error
	lea							r8, [r8 + 1]					; increment r8
	jmp							.check_base_tail				; otherwise jump back to loop

.is_base_valid:
	cmp							rcx, 0							; if at this point rcx is still 0, base len is 0
	je							.ft_atoi_base_err				; which is an error

;	below this point, base should be considered valid, or I fucked up...
	mov							r9, rcx							; store length of base in r9
	mov							rcx, -1							; set counter to -1

.skip_whitespace:
	inc							rcx
	cmp							byte [rdi + rcx], 32			; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 9				; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 10			; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 11			; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 12			; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 13			; skip space
	je							.skip_whitespace
	cmp							byte [rdi + rcx], 43			; check for +
	je							.atoi_base_main_inc
	cmp							byte [rdi + rcx], 45			; check for -
	je							.atoi_base_neg
	jmp							.atoi_base_main

.atoi_base_neg:
	mov							r15, 1							; set somewhere we need a negative number

.atoi_base_main_inc:
	inc							rcx

.atoi_base_main:
	cmp							byte [rdi + rcx], 0
	je							.atoi_base_done
	mov							r14b, byte [rdi + rcx]			; set current byte of rdi in a register
	mov							r8, -1

.find_in_base:
	inc							r8
	cmp							r8, r9							; check end of base
	je							.atoi_base_done
	cmp							r14b, byte [rsi + r8]			; compare byte in base with current byte
	je							.atoi_mul_and_add
	jmp							.find_in_base

.atoi_mul_and_add:
	mul							r9								; multiply by base
	add							rax, r8							; add current value
	jmp							.atoi_base_main_inc

	; find current char in base so rdi[rcx] = rsi[r8]
	; if found, multiply rax by r9 and add rsi[r8]

	pop							r15								; restore r15
	ret

.atoi_base_done:
	cmp							r15, 1
	je							.atoi_base_negate_result
	pop							r15								; restore r15
	ret

.atoi_base_negate_result:
	not							rax
	inc							rax
	pop							r15								; restore r15
	ret

.ft_atoi_base_err:
	mov							rax, 0
	pop							r15								; restore r15
	ret
