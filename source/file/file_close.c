/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:33:59 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:33:59 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_close(t_file *self)
{
	if (self->is_open == true)
	{
		self->fd = close(self->fd);
		self->is_open = false;
	}
	return (self);
}
