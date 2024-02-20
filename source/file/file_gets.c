/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:12 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:54:13 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static uint8_t	*file_get_next_line(t_file *self)
{
	struct s_allocator	*allocator;
	uint8_t				*line;
	uint64_t			ret;
	uint64_t			len;
	uint8_t				ch[2];

	ch[1] = 0;
	len = LINE_SIZE;
	allocator = self->allocator;
	line = allocator->alloc(allocator, len);
	while (1)
	{
		ret = (uint64_t)read(self->fd, ch, 1);
		self->pos++;
		if (string_lconcat(line, ch, len) == len + 1)
		{
			len = string_length(line);
			line = allocator->realloc(allocator, line, len, len * 2);
		}
		if (string_bsearch(line, '\n') != 0 || ret == 0)
			return (line);
	}
}

uint8_t	*file_gets(t_file *self)
{
	uint8_t				*line;
	uint8_t				*buffer;
	struct s_allocator	*allocator;

	allocator = self->allocator;
	buffer = (uint8_t[PAGE_SIZE]){0};
	if (self->buffered_io == true)
	{
		if (self->r == self->w)
			buffer_cache(self->buffer, self->fd);
		line = string_clone(allocator, (buffer_gets(self->buffer, buffer,
						PAGE_SIZE)));
		self->r = self->buffer->r;
		self->w = self->buffer->w;
		if (*line == 0)
			return (0);
		return (line);
	}
	else
		return (file_get_next_line(self));
}
