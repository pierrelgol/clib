/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 15:43:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char *string_replace_scalar(t_allocator *const allocator, const char *source, const int32_t scalar, const int32_t with)
{
	char    *result;
	uint64_t i;

	if (!source)
		return (NULL);
	result = memdupz(allocator, (void *) source);
	i = 0;
	while (result[i])
	{
		if (result[i] == scalar)
			result[i] = with;
		++i;
	}
	return (result);
}

char *string_replace_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters, const int32_t with)
{
	char    *result;
	uint64_t i;

	if (!source)
		return (NULL);
	result = memdupz(allocator, (void *) source);
	i = 0;
	while (result[i])
	{
		if (bitset_is_set(delimiters, result[i]))
			result[i] = with;
		++i;
	}
	return (result);
}

char *string_replace_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters, const int32_t with)
{
	char    *result;
	uint64_t i;

	if (!source)
		return (NULL);
	result = memdupz(allocator, (void *) source);
	i = 0;
	while (result[i])
	{
		if (!bitset_is_set(delimiters, result[i]))
			result[i] = with;
		++i;
	}
	return (result);
}

char *string_replace_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch), const int32_t with)
{
	char    *result;
	uint64_t i;

	if (!source)
		return (NULL);
	result = memdupz(allocator, (void *) source);
	i = 0;
	while (result[i])
	{
		if (predicate(result[i]))
			result[i] = with;
		++i;
	}
	return (result);
}

// char *string_replace_sequence(t_allocator *const allocator, const char *haystack, const char *needle, const char *with)
// {
// }
