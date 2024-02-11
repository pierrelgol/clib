/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:25:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:25:57 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	memory_compare(const void *s1, const void *s2, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		if (*((const uint8_t *)s1 + i) != *((const uint8_t *)s2 + i))
			return (*((const uint8_t *)s1 + i) - *((const uint8_t *)s2 + i));
		++i;
	}
	return (0);
}
