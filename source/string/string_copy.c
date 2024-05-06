/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:44:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 12:44:38 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_copy(char *dest, const char *src, const uint64_t destsize)
{
	uint64_t	i;

	if (!dest || !src || destsize == 0)
		return (string_length(src));
	i = 0;
	while (*src && i < (destsize - 1))
		dest[i++] = *src++;
	dest[i] = 0x00;
	return (i);
}

uint64_t	string_ccopy(char *dest, const int32_t ch, const char *src,
		const uint64_t destsize)
{
	char		*d;
	char		*s;
	uint64_t	i;

	if (!dest || !src || destsize == 0)
		return (0);
	i = 0;
	d = dest;
	s = src;
	while (i < destsize)
	{
		if (*(s + i) == (uint8_t)ch)
			return (i + 1);
		*(d + i) = *(s + i);
		++i;
	}
	return (0);
}

uint64_t	string_lcopy(char *dst, const char *src, uint64_t dsize)
{
	uint64_t	i;

	i = 0;
	if (dsize == 0)
		return (string_length(src));
	while (src[i] && (i + 1) < dsize)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0x00;
	return (string_length(src));
}
