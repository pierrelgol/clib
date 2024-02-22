/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:33:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:33:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*memory_move(void *dst, const void *src, uint64_t len)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dst == src || len == 0)
		return (dst);
	d = dst;
	s = src;
	if (dst > src)
	{
		while (len > 0)
		{
			*(d + len - 1) = *(s + len - 1);
			--len;
		}
	}
	while (len > 0)
	{
		*d++ = *s++;
		--len;
	}
	return (dst);
}
