/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:11:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/10 14:11:57 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char *string_join_one(t_allocator *const allocator, const char *s1, const char *s2)
{
	char    *result;
	uint64_t s1len;
	uint64_t s2len;
	uint64_t len;

	if (!s1 || !s2)
		return (NULL);
	s1len = string_length(s1);
	s2len = string_length(s2);
	len = s1len + s2len;
	result = memalloc(allocator, len + 1);
	string_copy(result, s1, len + 1);
	string_copy(&result[s1len], s2, len + 1);
	result[len] = 0x00;
	return (result);
}

char *string_join_many(t_allocator *const allocator, const char **strings)
{
	char    *result;
	uint64_t len;
	uint64_t i;

	i = 0;
	len = 0;
	while (strings[i])
		len += string_length(strings[i++]);
	result = memalloc(allocator, len + 1);
	string_append_many_assume_capacity(result, &strings[1]);
	return (result);
}

char *string_join_many_scalar(t_allocator *const allocator, const char **strings, const int32_t scalar)
{
	char    *result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	i = 0;
	len = 1;
	while (strings[i])
		len += string_length(strings[i++]) + 1;
	result = memalloc(allocator, len + 1);
	i = 0;
	j = 0;
	while (strings[i])
	{
		if (i == 0)
			j += string_append_one_assume_capacity(&result[j], (char[2]){(char) scalar, 0});
		j += string_append_one_assume_capacity(&result[j], strings[i++]);
		if ((j + 1) != len)
			j += string_append_one_assume_capacity(&result[j], (char[2]){(char) scalar, 0});
	}
	return (result);
}

char *string_join_many_sequence(t_allocator *const allocator, const char **strings, const char *sep)
{
	char    *result;
	uint64_t slen;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	i = 0;
	slen = string_length(sep);
	len = slen;
	while (strings[i])
		len += string_length(strings[i++]) + slen;
	result = memalloc(allocator, len + 1);
	i = 0;
	j = 0;
	while (strings[i])
	{
		if (i == 0)
			j += string_append_one_assume_capacity(&result[j], sep);
		j += string_append_one_assume_capacity(&result[j], strings[i++]);
		if ((j + slen) != len)
			j += string_append_one_assume_capacity(&result[j], sep);
	}
	return (result);
}
