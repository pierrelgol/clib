/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:30:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:30:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	buffer_write(t_buffer *const self, char *const buf, const uint64_t size)
{
	uint64_t	write_space;
	uint64_t	written;

	write_space = buffer_unwrite_count(self);
	if (write_space < size)
			buffer_grow(self);
	written = string_copy_until_scalar(&self->ptr[self->write_count], buf, '\0', size);
	self->write_count += written;
	return (written);
}
