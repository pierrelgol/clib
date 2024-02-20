/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fopen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:34:15 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:34:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	file_fopen(t_file *self, char *path, char *mode)
{
	int32_t	flags;

	flags = (int32_t)file_mode(mode);
	self->fd = open(path, flags, 0644);
	if (self->fd == -1)
		return (false);
	self->mode = flags;
	return (true);
}
