/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:33:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 14:33:51 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_until_scalar(const char *source, const int32_t scalar)
{
	uint64_t	i;

	if (!source)
		return (0);
	i = 0;
	while (source[i])
	{
		if (source[i] == scalar)
			break ;
		++i;
	}
	return (i);
}

uint64_t	string_count_until_any(const char *source,
		t_bitset const *delimiters)
{
	uint64_t	i;

	if (!source)
		return (0);
	i = 0;
	while (source[i])
	{
		if (bitset_is_set(delimiters, source[i]))
			break ;
		++i;
	}
	return (i);
}

uint64_t	string_count_until_none(const char *source,
		t_bitset const *delimiters)
{
	uint64_t	i;

	if (!source)
		return (0);
	i = 0;
	while (source[i])
	{
		if (bitset_is_set(delimiters, source[i]))
			break ;
		++i;
	}
	return (i);
}

uint64_t	string_count_until_predicate(const char *source,
		t_fn_predicate *predicate)
{
	uint64_t	i;

	if (!source)
		return (0);
	i = 0;
	while (source[i])
	{
		if (predicate(source[i]))
			break ;
		++i;
	}
	return (i);
}

uint64_t	string_count_until_sequence(const char *haystack,
		const char *needle)
{
	uint64_t	haystack_len;
	uint64_t	needle_len;
	uint64_t	count;
	char		*haystack_end;

	if (!haystack || !needle)
		return (0);
	count = 0;
	needle_len = string_length(needle);
	haystack_len = string_length(haystack);
	haystack_end = (char*)haystack + haystack_len;
	while (haystack < haystack_end && string_ncompare(haystack, needle,
			needle_len) != 0)
	{
		++haystack;
		++count;
	}
	return (count);
}
