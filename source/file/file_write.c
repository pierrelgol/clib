/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:29 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	file_write(t_file *self, t_buffer *buffer, uint64_t size)
{
	uint64_t	total;
	uint8_t		ch;

	total = 0;
	while (self->offset != self->size && size-- > 0)
	{
		ch = self->buffer->data[self->offset++];
		buffer_write(buffer, ch);
		total++;
	}
	return (total);
}
