/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:40:17 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:40:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

uint8_t	*string_tokenize(uint8_t **string, const uint8_t *delim)
{
	uint8_t	*start;
	uint8_t	*end;

	start = *string;
	if (!*start)
		return (0);
	end = string_pbrk(start, delim);
	if (end)
	{
		*end = 0;
		*string = end + 1;
	}
	else
		*string = end;
	return (start);
}
