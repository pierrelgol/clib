/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:49:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:49:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_copy(uint8_t *dst, const uint8_t *src)
{
	uint64_t	i;

	i = string_length(src);
	memory_copy(dst, src, i);
	dst[i] = 0x00;
	return (dst);
}
