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

uint8_t	*string_tokenize(const uint8_t **string, const uint8_t *delim)
{
	uint8_t	*next;
	uint8_t	*token;

	if (**string == 0)
		return (0);
	token = (uint8_t *)string[0];
	next = (uint8_t *)string[0];
	next += string_cspan(next, delim);
	*next = 0x00;
	string[0] = (next + 1);
	return (token);
}
