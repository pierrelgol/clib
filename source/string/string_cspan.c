/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cspan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:22:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 15:22:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_cspan(const uint8_t *s, const uint8_t *charset)
{
	uint8_t		*set;
	uint64_t	span;

	if (!*s)
		return (0);
	set = (uint8_t[256]){0};
	while (*charset)
	{
		set[*charset] = 1;
		++charset;
	}
	span = 0;
	while (*s && set[*s] != 1)
	{
		++span;
		++s;
	}
	return (span);
}
