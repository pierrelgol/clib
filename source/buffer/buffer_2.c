/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:15:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:15:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool buffer_should_grow(t_buffer *const self, const uint64_t requested)
{
	if ((self->write_count + requested) >= self->capacity)
		return (true);
	return (false);
}

bool buffer_grow(t_buffer *self)
{
	char    *new_buffer;
	uint64_t new_size;

	new_size = self->capacity * 2;
	new_buffer = memalloc(self->allocator, new_size + 1);
	raw_copy(new_buffer, self->ptr, self->capacity);
	memdealloc(self->allocator, self->ptr);
	self->ptr = new_buffer;
	self->capacity = new_size;
	return (true);
}

int32_t buffer_getch(t_buffer *self)
{
	int32_t ch;

	if (self->read_count == self->write_count)
		return (0);
	ch = (int32_t) self->ptr[self->read_count++];
	buffer_compact(self);
	return ((int32_t) ch);
}

char *buffer_gets(t_buffer *const self, char *const dest, const uint64_t dsize)
{
	uint64_t unread_count;
	uint64_t written;
	uint64_t size;

	unread_count = buffer_unread_count(self);
	size = dsize;
	if (unread_count < size)
		size = unread_count;
	written = string_copy_until_scalar(dest, self->ptr, '\n', size);
	self->read_count += written + 1;
	buffer_compact(self);
	return (dest);
}

int32_t	buffer_putch(t_buffer *const self, const char ch)
{
	if (buffer_unwrite_count(self) == 0)
			buffer_grow(self);
	self->ptr[self->write_count++] = ch;
	return ((int32_t)ch);
}
