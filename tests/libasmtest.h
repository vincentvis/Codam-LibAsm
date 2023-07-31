/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libasmtest.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:04:44 by vincent       #+#    #+#                 */
/*   Updated: 2021/03/07 18:14:26 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASMTEST_H
# define LIBASMTEST_H

#include "libasm.h"
#include <stdlib.h>
#include <time.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <CoreServices/CoreServices.h>
#include <string.h>
#include <stdio.h>

#define LIST_EVENODD 0
#define LIST_COUNTED 1
#define LIST_ALPHREV 2
#define LIST_ALPH 3
#define LIST_ALPHABET 4
#define LIST_RANDOM  -1

#define OK_STR "\e[1;94mOK\x1b[0m"
#define FAIL_STR "\e[1;91mFAIL!!!!\x1b[0m"

char		*generate_str(size_t target_len);
char		*generate_str_alpha(size_t target_len);
char		*generate_str_with_args(int argc, char const *argv[], size_t *len_org);
uint64_t	getUptimeInMilliseconds(void);

void		generate_list(t_list **begin, int size, int show_count);
void		print_list(t_list *list);
void		print_list_prev_curr_next(t_list *prev);

#endif
