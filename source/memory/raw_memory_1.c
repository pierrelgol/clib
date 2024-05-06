/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_memory_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:27:03 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 16:27:04 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void *raw_alloc(const uint64_t size)
{
	char *ptr;

	ptr = malloc(size + (1 * (size == 0)));
	return (raw_zero(ptr, size + (1 * (size == 0))));
}

void *raw_dealloc(void *const ptr)
{
	free(ptr);
	return (NULL);
}

void *raw_resize(void *const ptr, const uint64_t osize, const uint64_t nsize)
{
	char *result;

	if (osize == nsize)
		return (ptr);
	result = raw_alloc(nsize);
	result = raw_copy(result, ptr, osize);
	return (result);
}

void *raw_dup(const void *ptr, const int64_t size)
{
	char *result;

	result = raw_alloc(size);
	result = raw_copy(result, ptr, size);
	return (result);
}

void *raw_dupz(const void *ptr)
{
	char    *result;
	uint64_t size;

	size = raw_search(ptr, 0x00, UINT64_MAX) - ptr;
	result = raw_alloc(size + 1);
	result = raw_copy(result, ptr, size);
	result[size] = 0x00;
	return (result);
}

