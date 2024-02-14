/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:25:31 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:25:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint8_t	buffer_write(t_buffer *self, uint8_t ch)
{
	if (buffer_is_full(self))
		buffer_growth(self);
	self->data[self->windex++] = ch;
	return (ch);
}
