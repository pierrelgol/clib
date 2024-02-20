/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_getch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:44 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:45 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	file_getch(t_file *self)
{
	int32_t	ch;

	if (self->buffered_io == true)
	{
		if (self->r == self->w)
			buffer_cache(self->buffer, self->fd);
		ch = buffer_getch(self->buffer);
		self->r = self->buffer->r;
		self->w = self->buffer->w;
	}
	else
	{
		ch = read(self->fd, &ch, 1);
		if (ch == 0)
			return (0);
		self->pos++;
	}
	return (ch);
}
