/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_pbrk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:27:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:27:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_pbrk(const uint8_t *s, const uint8_t *delim)
{
	uint8_t	*set;
	uint8_t	*ptr;

	if (!*s)
		return (0);
	set = (uint8_t[256]){0};
	while (*delim)
	{
		set[*delim] = 1;
		delim++;
	}
	ptr = (uint8_t *)s;
	while (*ptr)
	{
		if (set[*ptr])
			return (ptr);
		ptr++;
	}
	return (0);
}
