/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi_base_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:30:36 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:53:45 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

char *remove_dupl(char *str, size_t len)
{
	int	n;
	char *uniq;
	char has[256];

	uniq = malloc(len + 1);
	memset(has, 0, 255);
	memset(uniq, 0, len + 1);
	n = 0;
	while(len)
	{
		len--;
		if (has[(int)str[len]] == 0
			&& str[len] != '-'
			&& str[len] != '+')
		{
			uniq[n] = str[len];
			has[(int)str[len]] = 1;
			n++;
		}
	}
	return (uniq);
}

int	str_is_valid_base(char *str)
{
	int 	i = 0;
	char	has[256];

	memset(has, 0, 255);
	while (str[i])
	{
		if ((isalpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))
			&& (has[(int)str[i]] != 1))
		{
			has[(int)str[i]] = 1;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char *fallback_str = "+1234";
	char *fallback_base = "0123456789";

	char *str;
	char *base;

	str = fallback_str;
	base = fallback_base;

	if (argc >= 4)
	{
		// for generating some weird stuff
		str = generate_str(20);
		base = remove_dupl(str, 20);
	}
	else {
		if (argc >= 2)
			str = (char *)argv[1];
		if (argc >= 3)
			base = (char *)argv[2];
	}


	int ret = ft_atoi_base(str, base);
	int r = (int)strtoll(str, NULL, 0);
	printf("Atoi with base [%s] from str [%s]\n", base, str);
	printf("asm_atoi_base:\ni: %i | u: %u | hex: %x | octal: %o\n",
		ret, ret, ret, ret);
	if (errno == 0 && str_is_valid_base(base))
	{
		// compare to system strtoll only works for base 8,10,16
		printf("system strtoll (maybe):\ni: %i | u: %u | hex: %x | octal: %o\n",
			r, r, r, r);
	}
	printf("\n");

	(void)argc;
	(void)argv;
	return (0);
}
