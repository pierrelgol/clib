/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ncasecompare.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:45:59 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:46:01 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	string_ncasecompare(const char *s1, const char *s2, uint64_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (*p1 && (*p1 | 32) == (*p2 | 32) && n != 0)
	{
		++p1;
		++p2;
		--n;
	}
	return ((int32_t)(*p1 | 32) - (*p2 | 32));
}
