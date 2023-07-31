/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generate_things.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 12:42:06 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/07 18:13:44 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

void	print_list_prev_curr_next(t_list *prev)
{
	t_list *curr;
	t_list *next;
	t_list fail;

	fail.data = NULL;
	fail.next = NULL;

	curr = prev->next;
	next = NULL;
	if (curr)
		next = curr->next;
	if (!curr)
		curr = &fail;
	if (!next)
		next = &fail;
	printf(	"┌───────────────────┐\n"
			"│ %17p │\n"
			"│ d: %14p │ ┌───────────────────┐\n"
			"│ n: %14p ├─┤ %17p │\n"
			"└───────────────────┘ │ d: %14p │ ┌───────────────────┐\n"
			"                      │ n: %14p ├─┤ %17p │\n"
			"                      └───────────────────┘ │ d: %14p │ \n"
			"                                            │ n: %14p │\n"
			"                                            └───────────────────┘\n"
			,
			prev, prev->data, prev->next,
			curr, curr->data, curr->next,
			next, next->data, next->next);
}

void	print_list(t_list *list)
{
	t_list *tmp;
	int i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		printf("El: %i: [%p], data: %s (%p)\n",
			i,
			tmp,
			(tmp->data != NULL) ? tmp->data : NULL,
			tmp->data);
		i++;
		tmp = tmp->next;
	}
}

// ┌──────────────┐
// │ 0x7fbccfe00260 │
// │ d: 0x7fbccfe02760 │
// │ n: 0x0 │
// └──────────────┘

void	generate_list(t_list **begin, int size, int data_option)
{
	t_list *more;
	t_list *start;
	char *str;

	if (size == 0)
		return;

	*begin = malloc(sizeof(t_list));
	asprintf(&str, "begin of the list of size %i%c", size, 0);
	(*begin)->data = malloc(100);
	memcpy((*begin)->data, str, strlen(str));
	((char*)(*begin)->data)[strlen(str)] = 0;
	free(str);
	str = NULL;
	(*begin)->next = NULL;

	more = *begin;
	start = *begin;
	int i = 1;
	while (i < size)
	{
		more->next = malloc(sizeof(t_list));
		more->next->data = malloc(100);
		if (data_option == 0)
			asprintf(&str, "%s element", (i % 2 == 0) ? "Even" : "Odd");
		else if (data_option == 1)
			asprintf(&str, "Element %i, %s", i, (i % 2 == 0) ? "even" : "odd");
		else if (data_option == 2)
			asprintf(&str, "%c alpharev", 123 - i);
		else if (data_option == 3)
			asprintf(&str, "%c alpha", 64 + i);
		else if (data_option == 4)
			str = generate_str_alpha(10);
		else
			str = generate_str(10);
		memcpy(more->next->data, str, strlen(str));
		free(str);
		str = NULL;
		more->next->next = NULL;
		more = more->next;
		i++;
	}
	*begin = start;
}

char *generate_str_with_args(int argc, char const *argv[], size_t *len_org)
{
	*len_org = 0;
	if (argc > 2)
		*len_org = strtoll(argv[1], NULL, 10);
	if (*len_org <= 0)
		*len_org = rand() % 328;
	return (generate_str(*len_org));
}

char *generate_str_alpha(size_t target_len)
{
	char	*str;
	size_t	len;
	char	c;

	str = malloc((sizeof(char) * (target_len)) + 1);
	len = 0;
	while(len < target_len)
	{
		c = rand() % 27;
		c += 65;
		c += (rand() % 2 == 0) ? 32 : 0;
		str[len] = c;
		len++;
	}
	str[len] = 0;
	return str;
}

char *generate_str(size_t target_len)
{
	char *str;
	size_t	len;

	str = malloc((sizeof(char) * (target_len)) + 1);
	len = 0;
	while(len < target_len)
	{
		str[len] = (rand() % 92) + 32;
		len++;
	}
	str[len] = 0;
	return str;
}

uint64_t getUptimeInMilliseconds(void)
{
    static mach_timebase_info_data_t s_timebase_info;

    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        (void) mach_timebase_info(&s_timebase_info);
    });

    // mach_absolute_time() returns billionth of seconds,
    return (uint64_t)((mach_absolute_time() * s_timebase_info.numer));
}
