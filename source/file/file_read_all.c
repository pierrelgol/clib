/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:35 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:36 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_buffer	*file_read_all(t_file *self)
{
	uint8_t	*buffer;

	buffer = self->buffer->data;
	read(self->fd, buffer, self->size);
	self->buffer->windex = self->size;
	return (self->buffer);
}
