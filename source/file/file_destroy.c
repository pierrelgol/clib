/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:33:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:33:48 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_destroy(t_file *self)
{
	if (self->is_open)
		file_close(self);
	if (self->path != 0)
		self->allocator->dealloc(self->allocator, self->path);
	if (self->basename != 0)
		self->allocator->dealloc(self->allocator, self->basename);
	if (self->buffer != 0)
		buffer_destroy(self->allocator, self->buffer);
	self->allocator->dealloc(self->allocator, self);
	return (0);
}
