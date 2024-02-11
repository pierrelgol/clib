/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bsearch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:27:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:27:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_bsearch(const uint8_t *s, int32_t c)
{
	if (c == 0x00)
		return ((uint8_t *)&s[string_length(s)]);
	else
		return (memory_search(s, c, string_length(s)));
}
