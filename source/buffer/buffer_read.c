/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:25:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:25:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	buffer_read(t_buffer *self, uint8_t ch)
{
	if (buffer_is_empty(self))
		return (0);
	self->data[self->rindex++] = ch;
	return (ch);
}
