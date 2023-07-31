/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlen_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 12:24:41 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:20:12 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

int main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char	*s;
	size_t	len, len_org, sy_len;

	s = generate_str_with_args(argc, argv, &len_org);
	len = ft_strlen(s);
	sy_len = strlen(s);
	printf("str: [%s]\n"
		"ft:%3zu - sy:%3zu - gen:%3zu\n"
		"Equal: %s\n", s, len, sy_len, len_org, (len == sy_len) ? OK_STR : FAIL_STR);
	return (0);
}
