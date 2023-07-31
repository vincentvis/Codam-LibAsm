/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_push_front_main.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/12 14:55:20 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	t_list	*begin;

	generate_list(&begin, 2, 4);

	printf("List before:\n");
	print_list(begin);



	char *new_data;
	char *new_data2;
	new_data = strdup("New data for new element, should be second in list");
	new_data2 = strdup("This should be top element");

	ft_list_push_front(&begin, new_data);
	ft_list_push_front(&begin, new_data2);

	printf("list after:\n");
	print_list(begin);

	t_list *nulllist;
	nulllist = NULL;
	ft_list_push_front(&nulllist, "First and only element in list");
	printf("\nPushed where begin=NULL\n");
	print_list(nulllist);

	(void)argc;
	(void)argv;
	return (0);
}
