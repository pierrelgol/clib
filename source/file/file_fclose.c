/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fclose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:37 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:38 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	file_fclose(t_file *self)
{
	if (self->fd == -1 || self->is_open == false)
		return (false);
	if (close(self->fd) == -1)
		return (false);
	self->fd = -1;
	self->is_open = false;
	return (true);
}
