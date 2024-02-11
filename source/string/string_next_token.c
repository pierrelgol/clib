/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:14:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 14:14:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	string_next_token(struct s_allocator *allocator, uint8_t **string,
		uint8_t **out_token, const uint8_t *delim)
{
	uint8_t		*str;
	uint64_t	start;
	uint64_t	end;

	str = *string;
	if (*str == 0)
	{
		*out_token = 0;
		return ;
	}
	start = string_span(str, delim);
	end = string_cspan(&str[start], delim);
	*out_token = string_nclone(allocator, &str[start], end);
	string[0] = &string[0][start + end];
}
