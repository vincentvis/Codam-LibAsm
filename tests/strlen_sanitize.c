/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlen_sanitize.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 12:24:41 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:15:14 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

// just to show that fsanitize=address doesn't complain

int main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char	*s;
	char	fixed_size[22];
	size_t	len, len_org, sy_len;

	s = generate_str_with_args(argc, argv, &len_org);
	memcpy(fixed_size, s, 21);
	fixed_size[21] = 0;
	len = ft_strlen(fixed_size);
	sy_len = strlen(fixed_size);
	printf("str: [%s]\nft:%3zu - sy:%3zu - gen:%3zu\t\tEqual: %s\e[0m\n", fixed_size, len, sy_len, len_org, (len == sy_len) ? OK_STR : FAIL_STR);
	return (0);
}
