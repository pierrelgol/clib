/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_slcopy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:42:31 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 08:42:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static uint64_t	string_len_or_sentinel(const char *src, int32_t sentinel)
{
	uint64_t	len_or_sentinel_pos;

	len_or_sentinel_pos = 0;
	while (src[len_or_sentinel_pos] && src[len_or_sentinel_pos] != sentinel)
		len_or_sentinel_pos++;
	return (len_or_sentinel_pos);
}

uint64_t	string_slcopy(char *dst, const char *src, int32_t sentinel,
		uint64_t dsize)
{
	uint64_t	i;

	i = 0;
	if (dsize < 2)
		return (string_len_or_sentinel(src, sentinel));
	while (src[i] && src[i] != sentinel && (i + 2) < dsize)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = (char)sentinel;
	dst[i + 1] = 0x00;
	return (string_len_or_sentinel(src, sentinel));
}
