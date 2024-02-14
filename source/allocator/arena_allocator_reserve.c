/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_reserve.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:37:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:37:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	arena_new_arena_alloc(struct s_allocator *allocator, t_list *tail,
		uint64_t size)
{
	struct s_allocator	*parent;
	struct s_allocator	*arena;
	struct s_list		*node;

	parent = allocator->parent;
	node = list_create(parent);
	assert(node != 0);
	arena = arena_allocator_init(parent, size);
	assert(arena != 0);
	node->data = (uintptr_t)arena;
	node->next = 0;
	if (!tail)
		allocator->next = node;
	else
		tail->next = node;
}

void	arena_allocator_reserve(struct s_allocator *self, uint64_t size)
{
	struct s_allocator	*arena;
	struct s_list		*list;
	struct s_list		*prev;

	if ((self->count + size) < self->size)
		return ;
	if (!self->next)
		return (arena_new_arena_alloc(self, 0, size));
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
		return ;
	return (arena_new_arena_alloc(self, prev, size));
}
