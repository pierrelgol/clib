/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_putch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:51 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:52 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

int32_t	file_putch(t_file *self, char ch)
{
	int32_t	ret;

	if (self->buffered_io == true)
	{
		ch = (char)buffer_putch(self->buffer, ch);
		self->w = self->buffer->w;
		self->r = self->buffer->r;
	}
	else
	{
		ret = write(self->fd, &ch, 1);
		if (ret == -1)
			return (-1);
	}
	return (ch);
}
