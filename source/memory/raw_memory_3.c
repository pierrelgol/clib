/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_memory_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:16:54 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 10:16:55 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	raw_compare(const void *a, const void *b, const uint64_t size)
{
	unsigned char	*ptr_a;
	unsigned char	*ptr_b;
	uint64_t		i;

	i = 0;
	ptr_a = (unsigned char *)a;
	ptr_b = (unsigned char *)b;
	while (ptr_a[i] == ptr_b[i] && i < size)
		++i;
	return (ptr_a[i] - ptr_b[i]);
}

void	*raw_move(void *dst, const void *src, const uint64_t len)
{
	const char	*ptr_src;
	char		*ptr_dst;
	uint64_t	l;

	ptr_src = (const char *)src;
	ptr_dst = (char *)dst;
	l = len;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (l)
		{
			*(ptr_dst + len - 1) = *(ptr_src + len - 1);
			l--;
		}
		return (dst);
	}
	while (l--)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}
