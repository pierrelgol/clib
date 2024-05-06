/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:27:16 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 14:27:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_scalar(const char *source, const int32_t scalar,
		const uint64_t n)
{
	uint64_t	count;
	uint64_t	i;

	if (!source || !n)
		return (0);
	i = 0;
	count = 0;
	while (source[i])
	{
		if (source[i] == scalar)
			count += 1;
		++i;
	}
	return (count);
}

uint64_t	string_count_any(const char *source, t_bitset const *delimiters,
		const uint64_t n)
{
	uint64_t	count;
	uint64_t	i;

	if (!source || !n)
		return (0);
	i = 0;
	count = 0;
	while (source[i])
	{
		if (bitset_is_set(delimiters, source[i]))
			count += 1;
		++i;
	}
	return (count);
}

uint64_t	string_count_none(const char *source, t_bitset const *delimiters,
		const uint64_t n)
{
	uint64_t	count;
	uint64_t	i;

	if (!source || !n)
		return (0);
	i = 0;
	count = 0;
	while (source[i] && i < n)
	{
		if (!bitset_is_set(delimiters, source[i]))
			count += 1;
		++i;
	}
	return (count);
}

uint64_t	string_count_predicate(const char *source,
		t_fn_predicate *predicate, const uint64_t n)
{
	uint64_t	count;
	uint64_t	i;

	if (!source || !n)
		return (0);
	i = 0;
	count = 0;
	while (source[i] && i < n)
	{
		if (predicate(source[i]))
			count += 1;
		++i;
	}
	return (count);
}

uint64_t	string_count_sequence(const char *haystack, const char *needle,
		const uint64_t n)
{
	uint64_t	haystack_len;
	uint64_t	needle_len;
	uint64_t	count;
	uint64_t	i;

	if (!haystack || !needle)
		return (NOTFOUND);
	haystack_len = string_length(haystack);
	needle_len = string_length(needle);
	if (haystack_len < needle_len)
		return (NOTFOUND);
	i = 0;
	count = 0;
	while (i <= (haystack_len - needle_len))
	{
		if (raw_compare(&haystack[i], needle, needle_len) == 0)
			count += 1;
		if ((i + needle_len) >= n)
			break ;
		++i;
	}
	return (count);
}
