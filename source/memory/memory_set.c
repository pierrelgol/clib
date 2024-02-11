/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:52:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 10:52:24 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*memory_set(void *b, int32_t c, uint64_t len)
{
	uint64_t	i;

	i = 0;
	while (i < len)
		*((uint8_t *)b + i++) = (uint8_t)c;
	return (b);
}
