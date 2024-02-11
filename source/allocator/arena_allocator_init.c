/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:29:28 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:29:29 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

struct s_allocator	*arena_allocator_init(struct s_allocator *p, uint64_t s)
{
	struct s_allocator	*self;

	if (s < DEFAULT_SIZE)
		s = DEFAULT_SIZE;
	self = p->alloc(p, 1 * sizeof(struct s_allocator));
	self->parent = p;
	self->size = s;
	self->count = 0;
	self->region = p->alloc(self, s);
	memory_set(self->region, 0x2e, s);
	self->region[s - 1] = 0x00;
	self->alloc = arena_allocator_alloc;
	self->dealloc = arena_allocator_dealloc;
	self->realloc = arena_allocator_realloc;
	self->reserve = arena_allocator_reserve;
	self->next = 0;
	return (self);
}
