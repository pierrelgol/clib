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

char	*string_pbrk(const char *s, const char *delim)
{
	char	*set;
	char	*ptr;

	if (!*s)
		return (0);
	set = (char [256]){0};
	while (*delim)
	{
		set[(uint32_t)(*delim)] = 1;
		delim++;
	}
	ptr = (char *)s;
	while (*ptr)
	{
		if (set[(uint32_t)(*ptr)])
			return (ptr);
		ptr++;
	}
	return (0);
}
