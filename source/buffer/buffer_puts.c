/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_puts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:27:25 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 21:27:26 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	*buffer_puts(t_buffer *self, uint8_t *str)
{
	uint64_t	written;
	uint8_t		*ptr;

	ptr = &self->buffer[self->w];
	written = string_slcopy(&self->buffer[self->w], str, '\n',
			buffer_unwrite_count(self));
	self->w += written + 1;
	return (ptr);
}
