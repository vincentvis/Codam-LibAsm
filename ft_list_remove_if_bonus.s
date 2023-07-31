; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_list_remove_if_bonus.s                          :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/06 11:50:40 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:41 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
;	rdi = **begin_list
;	rsi = data_ref
;	rdx = function

section .text

global _ft_list_remove_if
extern _free
_ft_list_remove_if:
	test						rdi, rdi						;
	je							.fail_early						; return if (!begin_list)
	cmp							QWORD [rdi], 0					; = *begin_list == 0
	je							.fail_early						; return if (!(*begin_list))
	test						rsi, rsi						;
	je							.fail_early						; return if (!data_ref)
	test						rdx, rdx						;
	je							.fail_early						; return if (!cmp)

	push						r15								; r15 = callee save
	push						r14								; r14 = callee save
	push						rbp								; save stack base
	mov							rbp, rsp						; set new stack frame
	and							rsp, 0xfffffffffffffff0			; align stack on 4 byte boundary
	sub							rsp, 64							; make space for variables
	; things get "pushed" on top of rsp, so this makes 8*8 bytes available for use
	; and a push after this gets "on top" of that
	; so here I do rbp - 8 to get "closer" to rsp
	; i could do rsp + 48 to get to the same point, but if rsp moves (because push) it's fucked
	; things persist after calling external functions since the stack pointer is above this
	mov							QWORD [rbp - 8], rdi			; make sure rdi persists on stack
	mov							QWORD [rbp - 16], rsi			; make sure rsi persists on stack
	mov							QWORD [rbp - 24], rdx			; make sure rdx persists on stack
	mov							QWORD [rbp - 32], 0				; previous elem
	mov							r8, [rdi]						; = *begin_list
	mov							QWORD [rbp - 40], r8			; current elem
	mov							QWORD [rbp - 48], r8			; head elem

.head_loop:
	cmp							QWORD [rbp - 40], 0				; check if *current
	je							.remove_done
	mov							rdi, QWORD [rbp - 40]			; rdi = *begin_list
	mov							rdi, [rdi]						; rdi = (*begin_list)->data
	cmp							rdi, 0							; (*begin_list)->data != NULL
	je							.list_loop_start				; checking first elem is done
	mov							rsi, QWORD [rbp - 16]			; make sure rsi is properly set
	call						QWORD [rbp - 24]				; call compare function
	cmp							rax, 0							; check return of function
	je							.remove_head_elem				; if equal, remove elem
	jmp							.list_loop_start				; not equal, check rest of list

.remove_head_elem:
	mov							rdi, QWORD [rbp - 40]			; rdi = *begin_list
	mov							rdi, [rdi]						; rdi = (*begin_list)->data
	call						_free							; free((*begin_list)->data)
	mov							rdi, QWORD [rbp - 40]			; rdi = *begin_list
	mov							r8, [rdi + 8] 					; r8 = (*begin_list)->next
	mov							QWORD [rbp - 40], r8			; set current to next
	mov							QWORD [rbp - 48], r8			; set head to next
	call						_free							; free(*begin_list)
	jmp							.head_loop


.list_loop_start:
	mov							r8, QWORD [rbp - 40]			; set current element in r8
	mov							QWORD [rbp - 32], r8			; store current element as previous
	mov							r8, [r8 + 8]					; get next pointer
	mov							QWORD [rbp - 40], r8			; set next as current
.list_loop:
	cmp							QWORD [rbp - 40], 0				; check if *current
	je							.remove_done					;
	mov							rdi, QWORD [rbp - 40]			; rdi = *current
	mov							rdi, [rdi]						; rdi = (*current)->data
	cmp							rdi, 0							; check if data != NULL
	je							.list_loop_start				;
	mov							rsi, QWORD [rbp - 16]			; make sure rsi is set
	call						QWORD [rbp - 24]				; call compare function
	cmp							rax, 0							; check return of compare
	je							.remove_elem
	jmp							.list_loop_start

.remove_elem:
	mov							rdi, QWORD [rbp - 40]			; rdi = curr
	mov							rdi, [rdi]						; rdi = curr->data
	call						_free							; free curr->data
	mov							rdi, QWORD [rbp - 40]			; rdi = curr
	mov							r8, [rdi + 8]					; r8 = curr->next
	mov							QWORD [rdi], 0						; curr->data = NULL
	mov							r9, QWORD [rbp - 32]			; get prev in register
	mov							[r9 + 8], r8					; set prev->next to curr->next
	mov							QWORD [rbp - 40], r8			; set next as new current
	call						_free							; free curr
	jmp							.list_loop						; continue from current element


.remove_done:
	mov							r15, QWORD [rbp - 48]			; get head from saved variables
	mov							r14, QWORD [rbp - 8]			; get original rdi in r14
	mov							rsp, rbp						; reset stack top
	pop							rbp								; reset stack base
	mov							QWORD [r14], r15				; make sure head is correctly set
	pop							r14								; restore r14
	pop							r15								; restore r15
	ret

.fail_early:
	ret
