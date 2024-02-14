/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_realloc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:37:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:37:45 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_allocator_realloc(struct s_allocator *self, void *ptr,
		uint64_t osize, uint64_t nsize)
{
	void	*new_ptr;

	arena_allocator_reserve(self, nsize + 1);
	new_ptr = arena_allocator_alloc(self, nsize);
	memory_copy(new_ptr, ptr, osize);
	return (new_ptr);
}
