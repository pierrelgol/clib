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
#include <assert.h>

char	*string_clone(struct s_allocator *allocator, const char *string)
{
	char		*clone;
	uint64_t	len;

	assert(string != 0);
	assert(allocator != 0);
	len = string_length(string);
	clone = allocator->alloc(allocator, len + 1);
	clone = memory_copy(clone, string, len);
	clone[len] = 0x00;
	return (clone);
}
