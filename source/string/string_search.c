/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:45:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 12:45:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_search_scalar(const char *source, const int32_t scalar,
		const uint64_t n)
{
	uint64_t	i;

	if (!source || !n)
		return (NULL);
	if (scalar == '\0')
		return ((char *)&source[string_length(source)]);
	i = 0;
	while (i < n)
	{
		if (source[i] == scalar)
			return ((char *)&source[i]);
		++i;
	}
	return (NULL);
}

char	*string_search_any(const char *source, t_bitset const *delimiters,
		const uint64_t n)
{
	uint64_t	i;

	i = 0;
	if (!source || !delimiters || n == 0)
		return (NULL);
	while (i < n)
	{
		if (bitset_is_set(delimiters, source[i]))
			return ((char *)&source[i]);
		++i;
	}
	return (NULL);
}

char	*string_search_none(const char *source, t_bitset const *delimiters,
		const uint64_t n)
{
	uint64_t	i;

	i = 0;
	if (!source || !delimiters || n == 0)
		return (NULL);
	while (i < n)
	{
		if (!bitset_is_set(delimiters, source[i]))
			return ((char *)&source[i]);
		++i;
	}
	return (NULL);
}

char	*string_search_predicate(const char *source,
		bool(predicate)(int32_t ch), const uint64_t n)
{
	uint64_t	i;

	if (!source || !predicate || !n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (predicate(source[i]))
			return ((char *)&source[i]);
		++i;
	}
	return (NULL);
}

char	*string_search_sequence(const char *haystack, const char *needle,
		const uint64_t n)
{
	uint64_t	haystack_len;
	uint64_t	needle_len;
	uint64_t	i;

	if (!haystack || !needle)
		return (NULL);
	haystack_len = string_length(haystack);
	needle_len = string_length(needle);
	if (haystack_len < needle_len || n == 0 || n > haystack_len)
		return (NULL);
	i = 0;
	while (i <= (haystack_len - needle_len))
	{
		if (string_ncompare(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		if (i + needle_len >= n)
			break ;
		++i;
	}
	return (NULL);
}
