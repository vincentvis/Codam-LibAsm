/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:05:10 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"
#include "errno.h"
#include "unistd.h"

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	int		fildes;
	char	*buf;

	if (argc < 2)
	{
		printf("Please provide some arguments\narg1=num_bytes\narg2=fildes\narg3=ifset, read from current file\n");
		return (0);
	}

	int len = strtoll(argv[1], NULL, 10);
	if (len == 0)
		len = 50;
	buf = calloc(1, len + 1);

	fildes = 1;
	char *endptr;
	if (argc >= 3)
		fildes = strtoll(argv[2], &endptr, 10);
	if (fildes == 0 && endptr[0] != '\0')
		fildes = 1;

	if (argc >= 4)
	{
		// read from current file
		fildes = open(__FILE__, O_RDONLY);
	}

	printf("read %i bytes from fd: %i\n", len, fildes);
	int ret = ft_read(fildes, buf, len);
	if (ret > 0)
		printf("read: [%s]\n", buf);
	printf("return value: %i\n", ret);
	if (ret < 0)
	{
		printf("Error %i: [%s]\n", errno, strerror(errno));
	}
	return (0);
}
