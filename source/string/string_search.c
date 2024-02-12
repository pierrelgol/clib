/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:56:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:56:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_search(const uint8_t *haystack, const uint8_t *needle,
		uint64_t len)
{
	uint64_t	u1;
	uint64_t	u2;

	if (!haystack && len == 0)
		return (0);
	if (needle[0] == '\0')
		return ((uint8_t *)haystack);
	u1 = 0;
	while (haystack[u1])
	{
		u2 = 0;
		while (haystack[u1] && haystack[u1] == needle[u2] && u1 < len)
		{
			u2++;
			u1++;
		}
		if (!needle[u2])
			return ((uint8_t *)&haystack[(uint64_t)u1 - u2]);
		u1 = (u1 - u2) + 1;
	}
	return (0);
}
