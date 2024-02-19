/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:33:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:33:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static int32_t	file_mode(uint8_t *mode)
{
	if (mode[0] == 'r')
		return (O_RDONLY);
	if (mode[0] == 'w')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (mode[0] == 'a')
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (mode[0] == 'r' && mode[1] == '+')
		return (O_RDWR);
	if (mode[0] == 'w' && mode[1] == '+')
		return (O_RDWR | O_CREAT | O_TRUNC);
	if (mode[0] == 'a' && mode[1] == '+')
		return (O_RDWR | O_CREAT | O_APPEND);
	return (0);
}

t_file	*file_open(t_file *self, uint8_t *path, uint8_t *mode)
{
	self->mode = file_mode(mode);
	self->fd = open((char *)path, (int)self->mode);
	if (self->fd == -1)
	{
		self->is_open = false;
		return (0);
	}
	self->is_open = true;
	return (self);
}
