/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_growth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:25:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:25:45 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_buffer	*buffer_growth(t_buffer *self)
{
	struct s_allocator	*allocator;
	size_t				new_size;
	void				*new_data;

	allocator = self->allocator;
	new_size = self->size * 2;
	new_data = allocator->alloc(allocator, new_size);
	memory_copy(new_data, self->data, self->size);
	allocator->dealloc(allocator, self->data);
	self->data = new_data;
	self->size = new_size;
	return (self);
}
