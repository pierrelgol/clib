/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:01:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_substring(struct s_allocator *allocator, uint8_t const *s,
		uint64_t start, uint64_t len)
{
	uint8_t		*result;
	uint64_t	slen;
	uint64_t	i;

	i = 0;
	slen = string_length(s);
	if (start > slen)
		return (string_clone(allocator, (const uint8_t *)""));
	if (len > (slen - start))
		len = slen - start;
	result = allocator->alloc(allocator, (len + 1) * sizeof(uint8_t));
	while (i < len && s[start + i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0x00;
	return (result);
}
