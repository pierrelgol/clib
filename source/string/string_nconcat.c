/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_nconcat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:16:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:16:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_nconcat(uint8_t *s1, const uint8_t *s2, uint64_t n)
{
	uint8_t		*dest;
	uint64_t	i;

	i = string_length(s2);
	dest = memory_search(s1, 0x00, UINT64_MAX);
	dest = memory_copy(dest, s2, i);
	if (i < n)
		memory_set(dest, 0x00, (n - i));
	return (s1);
}
