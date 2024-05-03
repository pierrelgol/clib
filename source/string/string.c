/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:04:37 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/03 11:04:38 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t string_length(const char *string)
{
	const char *ptr;

	if (!string)
		return (0);
	ptr = string;
	while (*ptr)
		++ptr;
	return (ptr - string);
}

char *string_charset(char set[256], const char *charset)
{
	while (*charset)
		set[(int) (*charset++)] = 1;
	return (set);
}

char *string_create(t_allocator *allocator, const uint64_t size)
{
	char *result;

	if (!allocator)
		return (NULL);
	if (size == 0)
		return (allocator->dupz(allocator, "", 1));
	result = allocator->create(allocator, size);
	if (!result)
		return (0);
	return (result);
}

char *string_clone(t_allocator *allocator, const char *string)
{
	char    *result;
	uint64_t len;

	if (!allocator)
		return (NULL);
	len = string_length(string);
	if (len == 0)
		return (allocator->dupz(allocator, "", 1));
	result = allocator->dupz(allocator, string, len);
	if (!result)
		return (NULL);
	return (result);
}

char *string_nclone(t_allocator *allocator, const char *string, const uint64_t ssize)
{
	char    *result;
	uint64_t len;
	uint64_t n;

	if (!allocator)
		return (NULL);
	len = string_length(string);
	if (len == 0 || ssize == 0)
		return (allocator->dupz(allocator, "", 1));
	if (len < ssize)
		n = 0;
	if (len - n == 0)
		return (allocator->dupz(allocator, "", 1));
	result = allocator->dupz(allocator, string, len - n);
	if (!result)
		return (NULL);
	return (result);
}

char *string_slice(t_allocator *allocator, const char *string, uint64_t start, uint64_t size)
{
	char    *result;
	uint64_t len;

	if (!allocator)
		return (NULL);
	len = string_length(string);
	if (start > len)
		return (allocator->dupz(allocator, "", 1));
	else if (start + size > len)
		return (string_clone(allocator, &string[start]));
	else
		return (string_nclone(allocator, &string[start], size));
}

uint64_t string_safe_copy(char *dest, const char *src, const uint64_t destsize)
{
	uint64_t total;
	uint64_t len;
	uint64_t i;

	len = string_length(src);
	if (destsize == 0)
		return (len);
	i = 0;
	total = 0;
	while (src[i] && i < (destsize - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0x00;
	return (i);
}

uint64_t string_safe_ccopy(char *dest, const char *src, const char ch, const uint64_t destsize)
{
	uint64_t total;
	uint64_t len;
	uint64_t i;

	len = string_length(src);
	if (destsize == 0)
		return (len);
	i = 0;
	total = 0;
	while (src[i] && i < (destsize - 1))
	{
		if (src[i] == ch)
		{
			dest[i] = 0x00;
			return (i + 1);
		}
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0x00;
	return (i);
}

uint64_t string_safe_pcopy(char *dest, const char *src, t_predicate *predicate, const uint64_t destsize)
{
	uint64_t j;
	uint64_t i;

	i = 0;
	if (destsize == 0)
		return (string_length(src));
	while (src[i] && i < (destsize - 1))
	{
		if (predicate(src[i]) == true)
			dest[j++] = src[i++];
		else
			++i;
	}
	return (i);
}

int32_t string_compare(const char *str1, const char *str2)
{
	while (*str1 && *(unsigned char *) str1 == *(unsigned char *) str2)
	{
		++str1;
		++str2;
	}
	return (*(unsigned char *) str1 - *(unsigned char *) str2);
}

int32_t string_ncompare(const char *str1, const char *str2, const uint64_t n)
{
	uint64_t count;

	if (n == 0)
		return (0);
	count = n;
	while (*str1 && *(unsigned char *) str1 == *(unsigned char *) str2 && count--)
	{
		++str1;
		++str2;
	}
	return (*(unsigned char *) str1 - *(unsigned char *) str2);
}

int32_t string_casecompare(const char *str1, const char *str2)
{
	while (*str1 && ((*(unsigned char *) str1) | 32) == ((*(unsigned char *) str2) | 32))
	{
		++str1;
		++str2;
	}
	return (((*(unsigned char *) str1) | 32) - ((*(unsigned char *) str2) | 32));
}

int32_t string_ncasecompare(const char *str1, const char *str2, const uint64_t n)
{
	uint64_t count;

	if (n == 0)
		return (0);
	count = n;
	while (*str1 && ((*(unsigned char *) str1) | 32) == ((*(unsigned char *) str2) | 32) && count--)
	{
		++str1;
		++str2;
	}
	return (((*(unsigned char *) str1) | 32) - ((*(unsigned char *) str2) | 32));
}

uint64_t string_search_scalar(const char *string, const char scalar, const uint64_t ssize)
{
	uint64_t index;

	if (ssize == 0)
		return (NOTFOUND);
	index = 0;
	while (string[index])
	{
		if (string[index] == scalar)
			return (index);
		++index;
	}
	return (NOTFOUND);
}

uint64_t string_search_sequence(const char *string, const char *needle, const uint64_t len)
{
	uint64_t u1;
	uint64_t u2;

	if (len == 0)
		return (NOTFOUND);
	if (needle[0] == '\0')
		return (string_length(string));
	u1 = 0;
	while (string[u1])
	{
		u2 = 0;
		while (string[u1] && string[u1] == needle[u2] && u1 < len)
		{
			u2++;
			u1++;
		}
		if (!needle[u2])
			return ((uint64_t) u1 - u2);
		u1 = (u1 - u2) + 1;
	}
	return (NOTFOUND);
}

uint64_t string_search_any(const char *string, const char *charset, const uint64_t ssize)
{
	uint64_t index;
	char    *set;

	set = string_charset((char[256]){0}, charset);
	index = 0;
	while(string[index])
}
uint64_t string_search_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

bool string_contains_scalar(const char *string, const char scalar, const uint64_t ssize);
bool string_contains_sequence(const char *string, const char *needle, const uint64_t ssize);
bool string_contains_any(const char *string, const char *charset, const uint64_t ssize);
bool string_contains_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

bool string_starts_with_scalar(const char *string, const char scalar, const uint64_t ssize);
bool string_starts_with_sequence(const char *string, const char *needle, const uint64_t ssize);
bool string_starts_with_any(const char *string, const char *charset, const uint64_t ssize);
bool string_starts_with_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

bool string_ends_with_scalar(const char *string, const char scalar, const uint64_t ssize);
bool string_ends_with_sequence(const char *string, const char *needle, const uint64_t ssize);
bool string_ends_with_any(const char *string, const char *charset, const uint64_t ssize);
bool string_ends_with_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

uint64_t string_count_scalar(const char *string, const char scalar, const uint64_t ssize);
uint64_t string_count_sequence(const char *string, const char *needle, const uint64_t ssize);
uint64_t string_count_any(const char *string, const char *charset, const uint64_t ssize);
uint64_t string_count_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

uint64_t string_index_of_scalar(const char *string, const char scalar, const uint64_t ssize);
uint64_t string_index_of_sequence(const char *string, const char *needle, const uint64_t ssize);
uint64_t string_index_of_any(const char *string, const char *charset, const uint64_t ssize);
uint64_t string_index_of_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

uint64_t string_span_of_scalar(const char *string, const char scalar, const uint64_t ssize);
uint64_t string_span_of_sequence(const char *string, const char *needle, const uint64_t ssize);
uint64_t string_span_of_any(const char *string, const char *charset, const uint64_t ssize);
uint64_t string_span_of_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

uint64_t string_cspan_of_scalar(const char *string, const char scalar, const uint64_t ssize);
uint64_t string_cspan_of_sequence(const char *string, const char *needle, const uint64_t ssize);
uint64_t string_cspan_of_any(const char *string, const char *charset, const uint64_t ssize);
uint64_t string_cspan_of_predicate(const char *string, t_predicate *predicate, const uint64_t ssize);

char *string_filter_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t ssize);
char *string_filter_sequence(t_allocator *allocator, const char *string, const char *needle, const uint64_t ssize);
char *string_filter_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t ssize);
char *string_filter_predicate(t_allocator *allocator, const char *string, t_predicate *predicate, const uint64_t ssize);

char *string_trim_left_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_trim_left_sequence(t_allocator *allocator, const char *string, const char *needle, const uint64_t n);
char *string_trim_left_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_trim_left_predicate(t_allocator *allocator, const char *string, t_predicate *predicate, const uint64_t n);

char *string_trim_right_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_trim_right_sequence(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_trim_right_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_trim_right_predicate(t_allocator *allocator, const char *string, t_predicate *predicate, const uint64_t n);

char *string_trim_both_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_trim_both_sequence(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_trim_both_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_trim_both_predicate(t_allocator *allocator, const char *string, t_predicate *predicate, const uint64_t n);

char *string_pad_left_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_pad_left_sequence(t_allocator *allocator, const char *string, const char *needle, const uint64_t n);
char *string_pad_left_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);

char *string_pad_right_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_pad_right_sequence(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_pad_right_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);

char *string_pad_both_scalar(t_allocator *allocator, const char *string, const char scalar, const uint64_t n);
char *string_pad_both_sequence(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);
char *string_pad_both_any(t_allocator *allocator, const char *string, const char *charset, const uint64_t n);

char *string_append_one_assume_capacity(char *string, const char one);
char *string_append_one(t_allocator *allocator, const char *string, const char one);
char *string_append_many_assume_capacity(char *string, const char *many);
char *string_append_many(t_allocator *allocator, char *string, const char *many);

char *string_join_one(t_allocator *allocator, const char *string, const char *one);
char *string_join_one_sep(t_allocator *allocator, const char *string, const char *one, const char sep);
char *string_join_many(t_allocator *allocator, const char *string, const char **many);
char *string_join_many_sep(t_allocator *allocator, const char *string, const char **many, const char sep);

char *string_replace_scalar(char *string, const char scalar, const char with);
char *string_replace_sequence(t_allocator *allocator, const char *string, const char *needle, const char *with);
char *string_replace_any(t_allocator *allocator, const char *string, const char *charset, const char *with);
char *string_replace_predicate(t_allocator *allocator, const char *string, t_predicate *predicate, const char with);

char **string_split_scalar(t_allocator *allocator, const char *string, const char scalar);
char **string_split_sequence(t_allocator *allocator, const char *string, const char *sequence);
char **string_split_any(t_allocator *allocator, const char *string, const char *charset);
char **string_split_predicate(t_allocator *allocator, const char *string, t_predicate *predicate);
void string_split_destroy(t_allocator *allocator, char **split);

char *string_to_lower(char *string);
char *string_to_upper(char *string);
char *string_to_capitalize(char *string);
char *string_to_title(char *string);
char *string_to_reverse(char *string);

t_string_iterator *string_iterator_create(t_allocator *allocator);
t_string_iterator *string_iterator_init_scalar(t_string_iterator *iterator, const char *string, const char scalar);
t_string_iterator *string_iterator_init_sequence(t_string_iterator *iterator, const char *string, const char *needle);
t_string_iterator *string_iterator_init_any(t_string_iterator *iterator, const char *string, const char *charset);
t_string_iterator *string_iterator_on_event_skip(t_string_iterator *iterator, t_predicate *predicate);
t_string_iterator *string_iterator_on_event_match(t_string_iterator *iterator, t_predicate *predicate);
t_string_iterator *string_iterator_init_predicate(t_string_iterator *iterator, const char *string, t_predicate *predicate);
t_string_iterator *string_iterator_deinit(t_string_iterator *iterator);
t_string_iterator *string_iterator_destroy(t_string_iterator *iterator);
