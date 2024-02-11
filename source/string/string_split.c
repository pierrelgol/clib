/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:25:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:25:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	**string_split(struct s_allocator *allocator, const uint8_t *string,
		const uint8_t *delim)
{
	uint8_t		**result;
	uint8_t		*ptr;
	uint64_t	size;
	uint64_t	i;

	size = string_count_token(string, delim);
	result = allocator->alloc(allocator, size * sizeof(uint8_t *) + 1);
	i = 0;
	ptr = (uint8_t *)string;
	while (i < size)
		string_next_token(allocator, &ptr, (result + i++), delim);
	result[i] = 0x00;
	return (result);
}
