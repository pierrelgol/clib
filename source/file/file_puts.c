/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_puts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:03 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:54:04 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

uint64_t	file_puts(t_file *self, char *str)
{
	uint64_t	ret;

	if (self->buffered_io == true)
	{
		ret = self->buffer->w;
		buffer_puts(self->buffer, str);
		self->w = self->buffer->w;
		self->r = self->buffer->r;
		ret = self->buffer->w - ret;
	}
	else
		ret = write(self->fd, str, string_length(str));
	return (ret);
}
