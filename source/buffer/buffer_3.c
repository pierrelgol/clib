/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:24:02 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:24:02 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char *buffer_puts(t_buffer *const self, const char *str)
{
	uint64_t written;
	char    *ptr;

	ptr = &self->ptr[self->write_count];
	written = string_copy_until_scalar(ptr, str, '\n', buffer_unwrite_count(self));
	self->write_count += written + 1;
	return (ptr);
}

uint64_t buffer_read(t_buffer *const self, char *const buf, const uint64_t size)
{
	uint64_t unread_left;
	uint64_t read_count;
	uint64_t destsize;

	unread_left = buffer_unread_count(self);
	destsize = size;
	if (destsize >= unread_left)
		destsize = unread_left;
	read_count = string_copy_until_scalar(buf, self->ptr, '\0', destsize);
	self->read_count += read_count;
	buffer_compact(self);
	return (read_count);
}

uint64_t	buffer_reserve(t_buffer *const self, const uint64_t size)
{
	char				*new_buffer;
	uint64_t			new_size;

	new_size = self->capacity + size;
	new_buffer = memalloc(self->allocator, new_size + 1);
	raw_copy(new_buffer, self->ptr, self->capacity);
	memdealloc(self->allocator, self->ptr);
	self->ptr = new_buffer;
	self->capacity = new_size;
	return (new_size);
}

uint64_t	buffer_unread_count(t_buffer *const self)
{
	if (self->read_count > self->write_count)
		return (0);
	return (self->write_count - self->read_count);
}

uint64_t	buffer_unwrite_count(t_buffer *const self)
{
	return (self->capacity - self->write_count);
}
