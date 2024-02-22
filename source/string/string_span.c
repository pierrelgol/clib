/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_span.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:22:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 15:22:16 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_span(const char *s, const char *charset)
{
	char		*set;
	uint64_t	span;

	if (!*s)
		return (0);
	set = (char [256]){0};
	while (*charset)
	{
		set[(uint32_t)(*charset)] = 1;
		++charset;
	}
	span = 0;
	while (*s && set[(uint32_t)(*s)] == 1)
	{
		++span;
		++s;
	}
	return (span);
}
