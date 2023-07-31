/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_size_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:31:30 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	t_list	*begin;

	int sizearg;
	sizearg = (rand() % 20) + 3;
	if (argc >= 2)
		sizearg = strtoll(argv[1], NULL, 10);

	generate_list(&begin, sizearg, LIST_COUNTED);

	int listsize = ft_list_size(begin);

	printf("Size: %2i counted: %2i, %s\n", sizearg, listsize, (sizearg == listsize) ? OK_STR : FAIL_STR);

	(void)argc;
	(void)argv;
	return (0);
}
