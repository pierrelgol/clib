/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:08:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:08:57 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_buffer *buffer_create(struct s_allocator *const allocator)
{
	t_buffer *buffer;

	buffer = memalloc(allocator, sizeof(t_buffer));
	buffer->allocator = allocator;
	buffer->ptr = memalloc(allocator, BUFFER_CAPACITY + 1);
	buffer->read_count = 0;
	buffer->write_count = 0;
	buffer->capacity = BUFFER_CAPACITY;
	buffer->fdin = -1;
	buffer->fdout = -1;

	return (buffer);
}

t_buffer *buffer_destroy(t_buffer *const self)
{
	memdealloc(self->allocator, self->ptr);
	memdealloc(self->allocator, self);

	return (NULL);
}

bool buffer_clear(t_buffer *const self)
{
	raw_fill(self->ptr, 0x00, self->capacity);
	self->read_count = 0;
	self->write_count = 0;

	return (self);
}

void buffer_compact(t_buffer *const self)
{
	uint64_t bytes_remaining;

	if (self->read_count > self->write_count)
		bytes_remaining = 0;
	else
		bytes_remaining = self->write_count - self->read_count;
	if (bytes_remaining > 0)
	{
		raw_move(self->ptr, self->ptr + self->read_count, bytes_remaining);
		self->read_count = 0;
		self->write_count = bytes_remaining;
	}
	else
	{
		self->read_count = 0;
		self->write_count = 0;
	}
}

uint64_t buffer_cache(t_buffer *const self, const int32_t fd)
{
	char    *buffer;
	uint64_t rsize;

	buffer = (char[BUFFER_CAPACITY]){0};
	buffer_reserve(self, BUFFER_CAPACITY);
	rsize = (uint64_t) read(fd, &buffer[self->write_count], BUFFER_CAPACITY - 1);
	self->write_count += rsize;
	return (rsize);
}
