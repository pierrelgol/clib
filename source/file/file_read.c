/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:19 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:54:20 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	file_read(t_file *self, char *buffer, uint32_t size)
{
	int32_t	rsize;

	rsize = read(self->fd, buffer, size);
	return (rsize);
}
