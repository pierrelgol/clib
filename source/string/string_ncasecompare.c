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

int32_t	string_ncasecompare(const uint8_t *s1, const uint8_t *s2, uint64_t n)
{
	while (*s1 && (*s1 | 32) == (*s2 | 32) && n != 0)
	{
		++s1;
		++s2;
		--n;
	}
	return ((int32_t)(*s1 | 32) - (*s2 | 32));
}
