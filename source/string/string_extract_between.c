/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_extract_between.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:04:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/10 13:04:19 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char *string_extract_between_scalar(t_allocator *const allocator, const char *source, const int32_t scalar)
{
	uint64_t offset;
	uint64_t len;

	if (!source)
		return (NULL);
	offset = string_count_leading_scalar(source, scalar);
	len = string_count_until_scalar(&source[offset], scalar);
	return (string_nclone(allocator, &source[offset], len));
}

char *string_extract_between_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters)
{
	uint64_t offset;
	uint64_t len;

	if (!source)
		return (NULL);
	offset = string_count_leading_any(source, delimiters);
	len = string_count_until_any(&source[offset], delimiters);
	return (string_nclone(allocator, &source[offset], len));
}

char *string_extract_between_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters)
{
	uint64_t offset;
	uint64_t len;

	if (!source)
		return (NULL);
	offset = string_count_leading_none(source, delimiters);
	len = string_count_until_none(&source[offset], delimiters);
	return (string_nclone(allocator, &source[offset], len));
}

char *string_extract_between_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch))
{
	uint64_t offset;
	uint64_t len;

	if (!source)
		return (NULL);
	offset = string_count_leading_predicate(source, predicate);
	len = string_count_until_predicate(&source[offset], predicate);
	return (string_nclone(allocator, &source[offset], len));
}

char *string_extract_between_sequence(t_allocator *const allocator, const char *source, const char *needle)
{
	uint64_t offset;
	uint64_t len;

	if (!source)
		return (NULL);
	offset = string_count_leading_sequence(source, needle) * string_length(needle);
	len = string_count_until_sequence(&source[offset], needle);
	return (string_nclone(allocator, &source[offset], len));
}
