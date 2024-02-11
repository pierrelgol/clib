/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_allocator_destroy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:14:59 by pollivie          #+#    #+#             */
/*   Updated: 2024/01/30 13:15:00 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int64_t compare_entry(void *ptr1, void *ptr2)
{
	struct s_track_entry	*e1;
	struct s_track_entry	*e2;

	e1 = ptr1;
	e2 = ptr2;
	return (e1->ptr - e2->ptr);
}

struct s_list	*logging_allocator_is_double_free(struct s_allocator *self,
		const intptr_t *ptr)
{
	struct s_list			*node;
	struct s_track_entry	entry;

	entry.bytes = 0;
	entry.ptr = (intptr_t)ptr;
	node = list_search(self->freelist, &entry, compare_entry);
	if (node != 0)
		return (node);
	return (0);
}

static bool	logging_allocator_add_to_freelist(struct s_allocator *s,
		intptr_t *p)
{
	struct s_list			*node;
	struct s_track_entry	entry;

	entry.bytes = 0;
	entry.ptr = (intptr_t)p;
	node = list_pop_first(&s->refcount, &entry, compare_entry);
	if (node == 0)
	{
		dprintf(s->fd, "[deallocation][ptr: @%p][size: unknown][FAIL]\n", p);
		return (false);
	}
	else
	{
		entry = *(struct s_track_entry *)node->data;
		dprintf(s->fd, "[deallocation][ptr: @%p][size: %llu][OK  ]\n",
			(void *)entry.ptr, entry.bytes);
		list_push_at(&s->freelist, node, 0);
		s->deallocated += entry.bytes;
	}
	return (true);
}

void	*logging_allocator_dealloc(struct s_allocator *self, void *ptr)
{
	struct s_allocator		*parent;
	struct s_track_entry	*entry;
	struct s_list			*node;

	parent = self->parent;
	node = logging_allocator_is_double_free(self, ptr);
	if (node != 0)
	{
		entry = node->data;
		dprintf(self->fd, "[double free ][ptr: @%p][size: %llu][Err ]\n",
			(void *)entry->ptr, entry->bytes);
		return (0);
	}
	else
		logging_allocator_add_to_freelist(self, ptr);
	parent->dealloc(parent, ptr);
	return (0);
}
