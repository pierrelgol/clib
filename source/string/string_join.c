/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:14:13 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:14:14 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_join(struct s_allocator *allocator, const uint8_t *s1,
		const uint8_t *s2)
{
	uint8_t		*result;
	uint64_t	len1;
	uint64_t	len2;

	len1 = string_length(s1);
	len2 = string_length(s2);
	result = allocator->alloc(allocator, len1 + len2 + 1);
	memory_copy(result, s1, len1);
	memory_copy(&result[len1], s2, len2);
	result[len1 + len2] = 0x00;
	return (result);
}
