/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcmp_sanitize.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:27:52 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:14:42 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

// just to show that fsanitize=address doesn't complain

int	main(void)
{
	char	s1[10];
	char	s2[10];
	int		result_ft;
	int		result_sy;

	memcpy(s1, "aaaaaaaaa", 10);
	memcpy(s2, s1, 10);

	result_ft = ft_strcmp(s1, s2);
	result_sy = strcmp(s1, s2);
	printf("Should be equal: (%i==%i) %s\n", result_ft, result_sy, (result_ft == result_sy) ? OK_STR : FAIL_STR);
	return (0);
}
