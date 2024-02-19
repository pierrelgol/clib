/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:33:41 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:33:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_create(struct s_allocator *allocator, uint8_t *path,
		uint8_t *mode)
{
	t_file	*self;

	self = allocator->alloc(allocator, sizeof(t_file));
	self->allocator = allocator;
	self->size = file_size(path, mode);
	self->fd = -1;
	self->offset = 0;
	self->is_open = false;
	self->mode = 0;
	self->path = 0;
	self->basename = 0;
	self->buffer = buffer_create(allocator, self->size + 1);
	file_open(self, path, mode);
	file_read_all(self);
	return (self);
}
