/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_allocator_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:55:00 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:55:01 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

struct s_allocator	*dbg_allocator_init(struct s_allocator *p, bool flag)
{
	struct s_allocator	*priv;
	struct s_allocator	*self;

	priv = heap_init();
	self = priv->alloc(priv, 1 * sizeof(struct s_allocator));
	self->parent = p;
	self->priv = priv;
	self->alloc = dbg_allocator_alloc;
	self->dealloc = dbg_allocator_dealloc;
	self->realloc = dbg_allocator_realloc;
	self->reserve = dbg_allocator_reserve;
	self->count = 0;
	self->refcount = list_create(priv);
	self->allocated = 0;
	self->deallocated = 0;
	self->size = 0;
	self->fd = 2;
	if (flag)
		self->fd = open("log_file.log", O_CREAT | O_APPEND | O_RDWR, 0644);
	return (self);
}
