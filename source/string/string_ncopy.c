/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ncopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:53:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:53:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_ncopy(char *dst, const char *src, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (src[i] && n > 0)
	{
		dst[i] = src[i];
		++i;
		--n;
	}
	if (n > 0)
		memory_set(&dst[i], 0x00, n);
	return (dst);
}
