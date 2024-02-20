/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:00:26 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:00:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_destroy(t_file *self)
{
	struct s_allocator	*allocator;

	allocator = self->allocator;
	if (self->basename)
		allocator->dealloc(allocator, self->basename);
	if (self->path)
		allocator->dealloc(allocator, self->path);
	if (self->buffer)
		buffer_destroy(self->buffer);
	if (self->is_open)
		file_fclose(self);
	allocator->dealloc(allocator, self);
	return (0);
}
