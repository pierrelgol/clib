/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:02:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:02:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*memory_copy(void *dst, const void *src, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		*((uint8_t *)dst + i) = *((const uint8_t *)src + i);
		++i;
	}
	return (dst);
}
