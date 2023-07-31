/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:21:27 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"
#include "errno.h"
#include "unistd.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char *s;
	size_t len;
	int fildes;

	s = generate_str_with_args(argc, argv, &len);
	s[len-1] = '\n';

	fildes = 1;
	if (argc >= 3)
		fildes = strtoll(argv[2], NULL, 10);
	if (fildes == 0)
		fildes = 1;
	int ret = ft_write(fildes, s, len);
	printf("return value: %i, strlen: %zu\n", ret, len);
	if (ret >= 0)
		printf("Passed: %s\n", ((size_t)ret == len) ? OK_STR : FAIL_STR);
	if (ret < 0)
	{
		if (argc >= 3 && memcmp(argv[1], "badfildes", 10) == 0)
			printf("should be bad file descriptor: ");
		printf("Error %i: [%s]\n", errno, strerror(errno));
	}
	return (0);
}
