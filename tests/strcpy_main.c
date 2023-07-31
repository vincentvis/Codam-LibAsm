/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcpy_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:06:37 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:17:16 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char *dst;
	char *src;
	size_t len_org;

	src = generate_str_with_args(argc, argv, &len_org);
	dst = calloc(1, len_org + 1);

	if (argc == 1)
	{
		src[len_org / 2] = (char)(rand() % 100) + 156;
		src[(len_org / 2) - 1] = (char)200;
	}

	printf("Copy str of len %zu\n", len_org);
	char *ret = ft_strcpy(dst, src);

	int memcmp_result = memcmp(dst, src, len_org);
	printf("Memcmp on strs: %s\n", (memcmp_result == 0) ? OK_STR : FAIL_STR);
	printf("Pointers equal: %s\n", (dst == ret) ? OK_STR : FAIL_STR);
	(void)argc;
	(void)argv;
	return (0);
}
