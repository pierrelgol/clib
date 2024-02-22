/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:04:48 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:04:49 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_concat(char *s1, const char *s2)
{
	char		*dest;
	uint64_t	i;

	i = string_length(s2);
	dest = memory_search(s1, 0x00, UINT64_MAX);
	dest = memory_copy(dest, s2, i);
	dest[i] = 0x00;
	return (s1);
}
