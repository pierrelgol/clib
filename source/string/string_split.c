/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:43:35 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/10 11:43:36 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char **string_split_scalar(t_allocator *const allocator, const char *source, const int32_t scalar)
{
	char   **result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	if (!source)
		return (memalloc(allocator, 1));
	len = string_count_scalar(source, scalar, string_length(source));
	result = memalloc(allocator, (len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		result[i] = string_extract_between_scalar(allocator, &source[j], scalar);
		j += string_count_leading_scalar(&source[j], scalar);
		j += string_length(result[i]);
		++i;
	}
	result[i] = NULL;
	return (result);
}

char **string_split_any(t_allocator *const allocator, const char *source, const t_bitset *delimiters)
{
	char   **result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	if (!source)
		return (memalloc(allocator, 1));
	len = string_count_any(source, delimiters, string_length(source));
	result = memalloc(allocator, (len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		result[i] = string_extract_between_any(allocator, &source[j], delimiters);
		j += string_count_leading_any(&source[j], delimiters);
		j += string_length(result[i]);
		++i;
	}
	result[i] = NULL;
	return (result);
}

char **string_split_none(t_allocator *const allocator, const char *source, const t_bitset *delimiters)
{
	char   **result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	if (!source)
		return (memalloc(allocator, 1));
	len = string_count_none(source, delimiters, string_length(source));
	result = memalloc(allocator, (len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		result[i] = string_extract_between_none(allocator, &source[j], delimiters);
		j += string_count_leading_none(&source[j], delimiters);
		j += string_length(result[i]);
		++i;
	}
	result[i] = NULL;
	return (result);
}

char **string_split_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t))
{
	char   **result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	if (!source)
		return (memalloc(allocator, 1));
	len = string_count_predicate(source, predicate, string_length(source));
	result = memalloc(allocator, (len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		result[i] = string_extract_between_predicate(allocator, &source[j], predicate);
		j += string_count_leading_predicate(&source[j], predicate);
		j += string_length(result[i]);
		++i;
	}
	result[i] = NULL;
	return (result);
}
char **string_split_sequence(t_allocator *const allocator, const char *source, const char *needle)
{
	char   **result;
	uint64_t len;
	uint64_t i;
	uint64_t j;

	if (!source)
		return (memalloc(allocator, 1));
	len = string_count_sequence(source, needle, string_length(source));
	result = memalloc(allocator, (len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		result[i] = string_extract_between_sequence(allocator, &source[j], needle);
		j += string_count_leading_sequence(&source[j], needle);
		j += string_length(result[i]);
		++i;
	}
	result[i] = NULL;
	return (result);
}
