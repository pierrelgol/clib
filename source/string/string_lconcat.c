/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_lconcat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:23:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:24:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_lconcat(char *dst, const char *src, uint64_t size)
{
	uint64_t	total;
	uint64_t	dlen;
	uint64_t	slen;

	if ((!dst || !src) && !size)
		return (0);
	dlen = string_length(dst);
	slen = string_length(src);
	if (!size)
		return (slen);
	total = slen + dlen;
	if (dlen > size)
		return (slen + size);
	slen = 0;
	while (src[slen] && dlen + slen < size - 1)
	{
		dst[dlen + slen] = src[slen];
		slen++;
	}
	dst[dlen + slen] = 0x00;
	if (total >= dlen + size && dlen > total - dlen)
		return (dlen + size);
	return (total);
}
