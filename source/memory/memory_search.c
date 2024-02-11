/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:30:12 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:30:13 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void *memory_search(const void *s, int32_t c, uint64_t n)
{
	uint64_t	i;

	if (n == 0)
		return ((void*)s);
	i = 0;
	while (i < n)
	{
		if (*((const uint8_t *)s + i) == (const uint8_t)c)
			return ((uint8_t *)s + i);
		++i;
	}
	return (0);
}
