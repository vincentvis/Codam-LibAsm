/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_sort_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:35:21 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:31:02 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

static void	is_list_sorted(t_list *list)
{
	t_list	*current;
	t_list	*previous;
	int		cmp;
	int		fail;

	current = list->next;
	previous = list;
	fail = 0;
	while (current)
	{
		if (previous->data != NULL && current->data != NULL)
		{
			cmp = strcmp(previous->data, current->data);
			if (cmp > 0)
			{
				printf("%s\n", FAIL_STR);
				fail = 1;
				break ;
			}
		}
		current = current->next;
		previous = previous->next;
	}
	if (fail == 0)
		printf("%s\n", OK_STR);
}

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	t_list	*begin;

	int sizearg;
	sizearg = (rand() % 20) + 3;
	if (argc >= 2)
		sizearg = strtoll(argv[1], NULL, 10);

	if (argc >= 3 && memcmp(argv[2], "evenodd", 8) == 0)
	{
		printf("sort list data is even/odd\n");
		generate_list(&begin, sizearg, LIST_EVENODD);
	}
	else if (argc >= 3 && memcmp(argv[2], "alpharev", 9) == 0)
	{
		printf("sort list data is alphabetical reversed\n");
		generate_list(&begin, sizearg, LIST_ALPHREV);
	}
	else
	{
		printf("sort list data is alphabetical random strings\n");
		generate_list(&begin, sizearg, LIST_ALPHABET);
	}

	if (argc >= 4 && memcmp(argv[3], "donull", 7) == 0)
	{
		free(begin->data);
		begin->data = NULL;
		free(begin->next->next->next->next->data);
		begin->next->next->next->next->data = NULL;
	}

	print_list(begin);
	ft_list_sort(&begin, strcmp);
	printf("sorted: ");
	is_list_sorted(begin);
	print_list(begin);
	printf("\n");

	return (0);
}

/*
// functions in C
// not this one, since this just swaps around strings and not list elements
void	list_sort_dataptr(t_list **begin_list, int (*cmp)())
{
	t_list	*elem;
	t_list	*prev;
	void 	*swap;
	int		resort;

	if (!begin_list || !cmp || !(*begin_list) || !(*begin_list)->data
		|| !(*begin_list)->next || !(*begin_list)->next->data)
		return;

	prev = *begin_list;
	elem = (*begin_list)->next;
	resort = 0;
	while (elem)
	{
		if (cmp(prev->data, elem->data) > 0)
		{
			swap = prev->data;
			prev->data = elem->data;
			elem->data = swap;
			resort = 1;
		}
		prev = elem;
		elem = elem->next;
	}
	if (resort)
		list_sort_dataptr(begin_list, cmp);
}

// this one swaps around the actual list elements
void	list_sort_elem(t_list **begin_list, int (*cmp)())
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;
	int		resort;

	if (!begin_list || !cmp || !(*begin_list) || !(*begin_list)->data
		|| !(*begin_list)->next || !(*begin_list)->next->data)
		return;
	resort = 0;


	// check head
	if (cmp((*begin_list)->data, (*begin_list)->next->data) > 0)
	{
		curr = *begin_list;
		next = (*begin_list)->next;
		printf("SWAP HEAD [%.10s][%.10s]\n", curr->data, next->data);
		print_list_prev_curr_next(*begin_list);
		*begin_list = next;
		curr->next = next->next;
		next->next = curr;
		print_list_prev_curr_next(*begin_list);
		resort = 1;
	}

	prev = *begin_list;
	curr = (*begin_list)->next;
	next = NULL;
	if (curr)
		next = curr->next;

	while (next)
	{
		if (cmp(curr->data, next->data) > 0)
		{
			printf("SWAP [%.10s][%.10s]\n", curr->data, next->data);
			print_list_prev_curr_next(prev);
			prev->next = next;
			curr->next = next->next;
			next->next = curr;
			print_list_prev_curr_next(prev);
			resort = 1;
		}
		prev = curr;
		curr = next;
		next = curr->next;
	}
	if (resort)
		list_sort_elem(begin_list, cmp);
}
*/
