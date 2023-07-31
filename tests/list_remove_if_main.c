/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_remove_if_main.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:41:54 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

// removes if sum of ascii value of first 2 chars in string are greater than 150
int first2chars_gt150(char *str1, char *str2)
{
	if ((str1[0] + str1[1]) > 150)
		return (1);
	(void)str2;
	return (0);
}

// removes fixed indexes
int	static_remove(char *str1, char *str2)
{
	static int c = 0;
	c++;
	if (c == 4 || c == 7 || c == 8 || c == 14 || c == 17)
		return (0);
	(void)str1;
	(void)str2;
	return (1);
}

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	t_list	*begin;

	int sizearg;
	sizearg = (rand() % 20) + 3;
	if (argc >= 2)
		sizearg = strtoll(argv[1], NULL, 10);

	if (argc >= 4 && memcmp(argv[3], "first2chars_gt150", 15) == 0)
		generate_list(&begin, sizearg, LIST_RANDOM);
	else
		generate_list(&begin, sizearg, LIST_EVENODD);

	char *data_ref;

	data_ref = strdup("Odd element");
	if (argc >= 3)
	{
		free(data_ref);
		data_ref = strdup(argv[2]);
	}

	if (sizearg > 3 && argc >= 4 && memcmp(argv[3], "make_NULL", 10) == 0)
	{
		free(begin->next->next->data);
		begin->next->next->data = NULL;
		free(begin->next->next->next->next->data);
		begin->next->next->next->next->data = NULL;
	}

	if (argc >= 4 && memcmp(argv[3], "static", 7) == 0)
	{
		printf("Before remove with 'static' which removes fixed indexies\n");
		print_list(begin);
		ft_list_remove_if(&begin, data_ref, static_remove);
	}
	else if (argc >= 4 && memcmp(argv[3], "first2chars_gt150", 15) == 0)
	{
		printf("Before remove with 'first2chars_gt150'\n");
		print_list(begin);
		ft_list_remove_if(&begin, data_ref, first2chars_gt150);
	}
	else
	{
		printf("Before remove with strcmp (%s)\n", data_ref);
		print_list(begin);
		ft_list_remove_if(&begin, data_ref, strcmp);
	}
	printf("After remove:\n");
	print_list(begin);
	printf("\n");

	(void)argc;
	(void)argv;
	return (0);
}

/*
// remove func in C
void	list_remove_if_c(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *current;
	t_list *prev;
	t_list *tmp;

	if (!begin_list || !(*begin_list) || !data_ref || !cmp)
		return;


	while ((*begin_list)->data && cmp(data_ref, (*begin_list)->data) == 0)
	{
		free((*begin_list)->data);
		tmp = (*begin_list)->next;
		free(*begin_list);
		*begin_list = tmp;
	}
	current = (*begin_list)->next;
	prev = *begin_list;
	printf("curr: %p\n", current);
	while (current)
	{
		if (current->data != NULL && cmp(data_ref, current->data) == 0)
		{
			free(current->data);
			tmp = current->next;
			free(current);
			current = tmp;
			prev->next = current;
			prev = current;
		}
		else
			current = current->next;
	}
	printf("curr: %p\n", current);
}
*/