/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_lcopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:59:54 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:59:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_lcopy(char *dst, const char *src, uint64_t dsize)
{
	uint64_t	i;

	i = 0;
	if (dsize == 0)
		return (string_length(src));
	while (src[i] && (i + 1) < dsize)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0x00;
	return (string_length(src));
}
