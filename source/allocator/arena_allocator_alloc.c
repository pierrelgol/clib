/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_alloc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:37:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:37:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	*arena_alloc(struct s_allocator *self, size_t size)
{
	void	*ptr;

	ptr = &self->region[self->count];
	self->count += size;
	return (ptr);
}

static void	*new_arena(struct s_allocator *self, t_list *tail, size_t size)
{
	struct s_allocator	*parent;
	struct s_allocator	*arena;
	struct s_list		*node;

	parent = self->parent;
	node = list_create(parent);
	assert(node != 0);
	arena = arena_allocator_init(parent, size);
	assert(arena != 0);
	node->data = (uintptr_t)(arena);
	node->next = 0;
	if (!tail)
		self->next = node;
	else
		tail->next = node;
	return (arena_alloc(arena, size));
}

void	*arena_allocator_alloc(struct s_allocator *self, uint64_t size)
{
	struct s_allocator	*arena;
	struct s_list		*list;
	struct s_list		*prev;

	if ((self->count + size) < self->size)
		return (arena_alloc(self, size));
	if (!self->next)
		return (new_arena(self, 0, size));
	list = self->next;
	while (list)
	{
		arena = (struct s_allocator *)list->data;
		if ((arena->count + size) <= arena->size)
			break ;
		prev = list;
		list = list->next;
	}
	if (list != 0)
		return (arena_alloc(arena, size));
	return (new_arena(self, prev, size));
}
