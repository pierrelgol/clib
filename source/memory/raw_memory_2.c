/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_memory_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:16:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 10:16:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void *raw_copy(void *const dst, const void *src, const uint64_t dstsize)
{
	unsigned char *ptr_a;
	unsigned char *ptr_b;
	uint64_t       i;

	if (dstsize == 0)
		return (dst);
	i = 0;
	ptr_a = (unsigned char *) dst;
	ptr_b = (unsigned char *) src;
	while (i < dstsize)
	{
		*ptr_a++ = *ptr_b++;
		++i;
	}
	return (dst);
}

void *raw_ccopy(void *const dst, const int32_t byte, const void *src, const uint64_t dstsize)
{
	unsigned char *s;
	unsigned char *d;
	uint64_t       i;

	i = 0;
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	while (i < dstsize)
	{
		if (*(s + i) == (uint8_t) byte)
			return (s + i + 1);
		*(d + i) = *(s + i);
		++i;
	}
	return (0);
}

void *raw_fill(void *const dst, const int32_t byte, const uint64_t dstsize)
{
	unsigned char *ptr;
	uint64_t       i;

	ptr = (unsigned char *) dst;
	i = 0;
	while (i < dstsize)
		ptr[i++] = byte;
	return (dst);
}

void *raw_zero(void *const dst, const uint64_t dstsize)
{
	unsigned char *ptr;
	uint64_t       i;

	ptr = (unsigned char *) dst;
	i = 0;
	while (i < dstsize)
		ptr[i++] = 0x00;
	return (dst);
}

void *raw_search(const void *s, const int32_t byte, const uint64_t dstsize)
{
	unsigned char *ptr;
	uint64_t       i;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < dstsize)
	{
		if (ptr[i] == byte)
			return ((unsigned char *) (s + i));
		++i;
	}
	return (NULL);
}

