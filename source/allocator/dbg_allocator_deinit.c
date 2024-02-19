/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_allocator_deinit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:08:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/01/30 14:08:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	deinit_list(struct s_allocator *self, t_list *list)
{
	struct s_allocator		*priv;
	struct s_track_entry	*entry;

	priv = self->priv;
	while (list)
	{
		entry = (struct s_track_entry *)list->data;
		if (entry != 0)
		{
			priv->dealloc(priv, entry);
		}
		list = list->next;
	}
	list_destroy(priv, list);
}

struct s_allocator	*dbg_allocator_deinit(struct s_allocator *self)
{
	struct s_allocator	*priv;

	priv = self->priv;
	if (self->refcount)
		deinit_list(self, self->refcount);
	if (self->freelist)
		deinit_list(self, self->freelist);
	dprintf(self->fd, "Bytes allocated   : %8llu\n", self->allocated);
	dprintf(self->fd, "Bytes deallocated : %8llu\n", self->deallocated);
	if (self->fd != 0)
		close(self->fd);
	priv->dealloc(priv, self);
	heap_deinit(priv);
	return (0);
}
