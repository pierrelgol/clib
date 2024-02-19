/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:24 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

uint64_t	file_read(t_file *self, t_buffer *buffer, uint64_t size)
{
	uint8_t		*read_buffer;
	uint64_t	read_size;
	uint64_t	total;
	uint64_t	i;

	total = 0;
	read_size = 511;
	read_buffer = (uint8_t[512]){0};
	if (self->is_open == 0)
		return (0);
	while (read_size == 511)
	{
		read_size = read(self->fd, read_buffer, 511);
		i = 0;
		while (i < read_size && size-- > 0)
			buffer_write(buffer, read_buffer[i++]);
		total += i;
	}
	self->offset += total;
	return (total);
}
