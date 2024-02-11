/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:51:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:51:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*string_clone(struct s_allocator *allocator, const uint8_t *string)
{
	uint8_t		*clone;
	uint64_t	len;

	len = string_length(string);
	clone = allocator->alloc(allocator, len + 1);
	clone = memory_copy(clone, string, len);
	clone[len] = 0x00;
	return (clone);
}
