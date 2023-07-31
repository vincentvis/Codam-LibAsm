; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_list_sort_bonus.s                               :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/08 18:00:03 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:14 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	void ft_list_sort(t_list **begin_list, int (*cmp)(void *d1, void *d2));
;	Create the function ft_list_sort which sorts the list’s contents
;	by ascending order by comparing two links thanks to a function
;	that can compare the data held in those two links.
;
;	rdi = **begin_list
;	rsi = cmp
;
;	You can't put NULL in strcmp...
;
;	Strcmp returns ( <0 || 0 || >0 )
;	Ascending = "increasing size or value, moving upwards or to higher levels"
;	So "a" comes before "b"
;	but strcmp("a", "b") == -1
;	so -1 or other negative is GOOD
;	0 is also good
;	only >0 has to be swapped

section .text

global _ft_list_sort
_ft_list_sort:
	push						rbp								; save stack base
	mov							rbp, rsp						; set new stack frame
	and							rsp, 0xfffffffffffffff0			; align stack on 4 byte boundary
	sub							rsp, 32							; make space for variables
	push						r12								; = prev
	push						r13								; = curr
	push						r14								; = next
	push						r15								; = has swapped

	test						rdi, rdi						; check if **begin_list exists
	je							.done
	test						rsi, rsi						; check if cmp function exists
	je							.done
	mov							QWORD [rbp - 8], rdi			; never lose begin of list
	mov							QWORD [rbp - 16], rsi			; never lose track of cmp


.sort_elems_head:
	xor							r15, r15
	mov							r13, QWORD [rbp - 8]			; curr = **begin_list
	mov							r13, [r13]						; curr = *begin_list
	test						r13, r13						; test if not NULL
	je							.done							; if head = null we stop

	mov							r14, [r13 + 8]					; next = curr->next
	test						r14, r14						; test if not NULL
	je							.done							; if next = null we stop

	; compare(curr->data, next->data)
	; cmp    (rdi      , rsi )
	mov							rdi, [r13]						; rdi = curr->data
	mov							rsi, [r14]						; rsi = next->data
	test						rdi, rdi						; if rdi = null we skip to next
	je							.swap_head_elem							; because strcmp crashes with NULL
	test						rsi, rsi						; if rsi = null we skip to next
	je							.next					; same for rsi
	call						QWORD [rbp - 16]				; call compare function
	jle							.next							; jump to sorting rest if these two are fine
	; SWAP HEAD
	; r13 and r14 are callee save, so should be still here after calling cmp()
.swap_head_elem:
	mov							r15, 1							; resort = 1
	mov							r8, QWORD [rbp - 8]				; r8 = **begin_list
	mov							[r8], r14						; *begin_list = next
	mov							r9, [r14 + 8]					; r9 = next->next
	mov							[r13 + 8], r9					; curr->next = next->next
	mov							[r14 + 8], r13					; next->next = curr

.next:
	mov							r12, r13						; prev = curr
	mov							r13, r14						; curr = next
	mov							r14, [r13 + 8]					; next = curr->next
	test						r14, r14						; if next == null
	je							.maybe_done						; jump to maybe done

.sort_loop:
	mov							rdi, [r13]						; rdi = curr->data
	mov							rsi, [r14]						; rsi = next->data
	test						rdi, rdi						; check not null
	je							.swap_elem_rdi					; if null, maybe swap
	test						rsi, rsi						; check not null
	je							.next							; if null, swap
	call						QWORD [rbp - 16]				; call cmp
	jle							.next							; if lower or equal, go to next item
	; SWAP ITEM
.swap_elem:
	mov							r15, 1							; resort = 1
	mov							[r12 + 8], r14					; prev->next = next
	mov							r8, [r14 + 8]					; r8 = next->next
	mov							[r13 + 8], r8					; curr->next = next->next
	mov							[r14 + 8], r13					; next->next = curr;
	jmp							.next

.swap_elem_rdi:
	test						rsi, rsi						; if rsi is also NULL
	je							.next							; move to next
	jmp							.swap_elem						; otherwise swap

.maybe_done:
	cmp							r15, 0							; if there was a swap
	jne							.sort_elems_head				; start over

.done:
	pop							r15								; restore callee save registers
	pop							r14								; restore callee save registers
	pop							r13								; restore callee save registers
	pop							r12								; restore callee save registers
	mov							rsp, rbp						; restore stack pointer
	pop							rbp								; restore stack base
	ret
