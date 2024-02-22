/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_casecompare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:43:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:43:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	string_casecompare(const char *s1, const char *s2)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (*p1 && (*p1 | 32) == (*p2 | 32))
	{
		++p1;
		++p2;
	}
	return ((int32_t)(*p1 | 32) - (*p2 | 32));
}
