/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_index_of_last.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:08:46 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 14:17:03 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_index_of_last_scalar(const char *source,
		const int32_t scalar)
{
	uint64_t	last;
	uint64_t	i;

	if (!source)
		return (NOTFOUND);
	i = 0;
	last = 0;
	while (source[i])
	{
		if (source[i] == scalar)
			last = i;
		++i;
	}
	return (last);
}

uint64_t	string_index_of_last_any(const char *source,
		t_bitset const *delimiters)
{
	uint64_t	last;
	uint64_t	i;

	if (!source)
		return (NOTFOUND);
	i = 0;
	last = 0;
	while (source[i])
	{
		if (bitset_is_set(delimiters, source[i]))
			last = i;
		++i;
	}
	return (last);
}

uint64_t	string_index_of_last_none(const char *source,
		t_bitset const *delimiters)
{
	uint64_t	last;
	uint64_t	i;

	if (!source)
		return (NOTFOUND);
	i = 0;
	last = 0;
	while (source[i])
	{
		if (!bitset_is_set(delimiters, source[i]))
			last = i;
		++i;
	}
	return (last);
}

uint64_t	string_index_of_last_predicate(const char *source,
		bool(predicate)(int32_t ch))
{
	uint64_t	last;
	uint64_t	i;

	if (!source)
		return (NOTFOUND);
	i = 0;
	last = 0;
	while (source[i])
	{
		if (predicate(source[i]) == true)
			last = i;
		++i;
	}
	return (last);
}

uint64_t	string_index_of_last_sequence(const char *haystack,
		const char *needle)
{
	uint64_t	haystack_len;
	uint64_t	needle_len;
	uint64_t	last;
	uint64_t	i;

	if (!haystack || !needle)
		return (NOTFOUND);
	haystack_len = string_length(haystack);
	needle_len = string_length(needle);
	if (haystack_len < needle_len)
		return (NOTFOUND);
	i = 0;
	last = 0;
	while (i <= (haystack_len - needle_len))
	{
		if (raw_compare(&haystack[i], needle, needle_len) == 0)
			last = i;
		++i;
	}
	return (last);
}
