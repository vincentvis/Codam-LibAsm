/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcmp_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:06:37 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/28 11:13:47 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libasmtest.h"

#define MAX_CHARS_FOR_HUMAN_COMPARE 30

/*

	4 possible params:
	1 param: in[random, random_up, random_down]
		compare random strings and change nothing, or add/sub something
	2 params: 2 stings that will be compared
	4 params: 2 strings with first char subtituted for int in param 3 and 4

*/

int	main(int argc, char const *argv[])
{
	srand(getUptimeInMilliseconds());

	char	*s1;
	char	*s2;
	size_t	len;

	s2 = calloc(1, 200);
	s1 = calloc(1, 200);
	if (argc == 3)
	{
		memcpy(s1, argv[1], strlen(argv[1]));
		memcpy(s2, argv[2], strlen(argv[2]));
	}
	else if (argc == 2)
	{
		if (memcmp(argv[1], "random", 6) == 0)
		{
			free(s1);
			free(s2);
			s1 = NULL;
			s2 = NULL;
			len = (rand() % 150) + 25;
			s1 = generate_str(len);
			s2 = malloc(len + 1);
			memcpy(s2, s1, len);
			if (memcmp(argv[1], "random_up", 10) == 0)
				s1[len / 2] += rand() % 254;
			if (memcmp(argv[1], "random_down", 12) == 0)
				s1[len / 2] -= rand() % 254;
		}
		else
		{
			memcpy(s1, argv[1], strlen(argv[1]));
			memcpy(s2, argv[1], strlen(argv[1]));
		}
	}
	else if (argc == 5)
	{
		memcpy(s1, argv[1], strlen(argv[1]));
		memcpy(s2, argv[2], strlen(argv[2]));
		s1[0] = atoi(argv[3]);
		s2[0] = atoi(argv[4]);
	}
	else
	{
		memcpy(s1, "some default\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 31);
		memcpy(s2, "some default\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 31);
	}

	printf("Check if [%s] == [%s]\n", s1, s2);
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	printf("len1: %zu, len2: %zu\n", len1, len2);
	size_t i = 0;
	while (i <= len1 && i <= MAX_CHARS_FOR_HUMAN_COMPARE)
	{
		printf("%i,", s1[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i <= len2 && i <= MAX_CHARS_FOR_HUMAN_COMPARE)
	{
		printf("%i,", s2[i]);
		i++;
	}
	printf("\n");

	// before this point is just setup
	int ret_asm;
	int	ret_sys;
	// the actual comparison is called here:
	ret_asm = ft_strcmp(s1, s2);
	ret_sys = strcmp(s1, s2);
	printf("asm = %i, sys = %i, -- ", ret_asm, ret_sys);
	// this ugly AF check since different systems implement it differently
	// man says "returns int gt, eq or lt 0, according to s1 <=> s2"
	// but some systems give always [-1, 0 1], others give diff in ascii value
	if ((ret_asm < 0 && ret_sys < 0)
	 || (ret_asm == 0 && ret_sys == 0)
	 || (ret_asm > 0 && ret_sys > 0))
		printf("%s\n", OK_STR);
	else
		printf("%s\n", FAIL_STR);
	return (0);
}
