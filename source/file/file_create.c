/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:58:25 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 10:58:26 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_create(struct s_allocator *allocator, bool is_cached)
{
	t_file	*self;

	self = allocator->alloc(allocator, sizeof(t_file));
	self->allocator = allocator;
	self->buffered_io = is_cached;
	self->basename = 0;
	self->path = 0;
	self->fd = -1;
	self->mode = -1;
	self->flag = 0;
	self->pos = 0;
	self->size = 0;
	self->buffer = buffer_create(allocator, PAGE_SIZE, false);
	return (self);
}
