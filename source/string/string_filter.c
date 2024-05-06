/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:34:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 15:34:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_filter_scalar(t_allocator *const allocator, const char *source,
		const int32_t scalar)
{
	char		*result;
	uint64_t	len;
	uint64_t	i;

	if (!source)
		return (NULL);
	len = string_length(source);
	len -= string_count_scalar(source, scalar, len);
	result = memalloc(allocator, len + 1);
	i = 0;
	while (*source && i < len)
	{
		if (*source == scalar)
			++source;
		else
			result[i++] = *source++;
	}
	return (result);
}

char	*string_filter_any(t_allocator *const allocator, const char *source,
		t_bitset const *delimiters)
{
	char		*result;
	uint64_t	len;
	uint64_t	i;

	if (!source)
		return (NULL);
	len = string_length(source);
	len -= string_count_any(source, delimiters, len);
	result = memalloc(allocator, len + 1);
	i = 0;
	while (*source && i < len)
	{
		if (bitset_is_set(delimiters, *source))
			++source;
		else
			result[i++] = *source++;
	}
	return (result);
}

char	*string_filter_none(t_allocator *const allocator, const char *source,
		t_bitset const *delimiters)
{
	char		*result;
	uint64_t	len;
	uint64_t	i;

	if (!source)
		return (NULL);
	len = string_length(source);
	len -= string_count_none(source, delimiters, len);
	result = memalloc(allocator, len + 1);
	i = 0;
	while (*source && i < len)
	{
		if (!bitset_is_set(delimiters, *source))
			++source;
		else
			result[i++] = *source++;
	}
	return (result);
}

char	*string_filter_predicate(t_allocator *const allocator,
		const char *source, bool(predicate)(int32_t ch))
{
	char		*result;
	uint64_t	len;
	uint64_t	i;

	if (!source)
		return (NULL);
	len = string_length(source);
	len -= string_count_predicate(source, predicate, len);
	result = memalloc(allocator, len + 1);
	i = 0;
	while (*source && i < len)
	{
		if (predicate(*source))
			++source;
		else
			result[i++] = *source++;
	}
	return (result);
}

char	*string_filter_sequence(t_allocator *const allocator,
		const char *haystack, const char *needle)
{
	uint64_t	haystack_len;
	uint64_t	needle_len;
	uint64_t	filtered_len;
	char		*result;
	uint64_t	i;

	if (!haystack || !needle)
		return (NULL);
	haystack_len = string_length(haystack);
	needle_len = string_length(needle);
	filtered_len = haystack_len - string_count_leading_sequence(haystack,
			needle);
	result = memalloc(allocator, filtered_len + 1);
	i = 0;
	while (*haystack && i < filtered_len)
	{
		if (string_ncompare(haystack, needle, needle_len) == 0)
			haystack += needle_len;
		else
			result[i++] = *haystack++;
	}
	return (result);
}
