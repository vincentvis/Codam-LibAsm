/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strdup_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:18:48 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char *s;
	char *dupped;
	size_t len;

	s = generate_str_with_args(argc, argv, &len);

	dupped = ft_strdup(s);
	printf("Duplicated str of len %zu\n"
		"memcmp strings and strlen same: %s\n", len,
		(memcmp(s, dupped, len) == 0
			&& strlen(s) == strlen(dupped)
			&& s != dupped) ? OK_STR : FAIL_STR);
	return (0);
}
