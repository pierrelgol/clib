/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_allocator_alloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:14:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/01/30 13:14:51 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*dbg_allocator_alloc(struct s_allocator *self, uint64_t s)
{
	struct s_allocator		*parent;
	struct s_allocator		*priv;
	struct s_track_entry	*entry;
	intptr_t				*p;

	parent = self->parent;
	priv = self->priv;
	p = parent->alloc(parent, s);
	if (!p)
	{
		dprintf(self->fd, "[allocation  ][ptr: @%p][size: %8llu][FAIL]\n", NULL,
			s);
		return (0);
	}
	self->allocated += s;
	entry = priv->alloc(priv, sizeof(struct s_track_entry));
	entry->bytes = s;
	entry->ptr = (intptr_t)p;
	list_insert_at(priv, &self->refcount, (uintptr_t)entry, self->count++);
	dprintf(self->fd, "[allocation  ][ptr: @%p][size: %8llu][OK  ]\n", p, s);
	return (p);
}
