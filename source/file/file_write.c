/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:54:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	file_write(t_file *self, char *buffer, uint32_t size)
{
	int32_t	wsize;

	wsize = write(self->fd, buffer, size);
	return (wsize);
}
