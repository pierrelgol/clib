/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_rbsearch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:32:09 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:32:10 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_rbsearch(const char *s, int32_t c)
{
	uint64_t	i;

	if (c == 0x00)
		return ((char *)&s[string_length(s)]);
	i = string_length(s);
	while (i >= 1)
	{
		if (s[i - 1] == (int8_t)c)
			return ((char *)&s[i - 1]);
		--i;
	}
	return (0);
}
