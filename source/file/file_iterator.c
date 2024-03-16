/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_iterator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:44 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:54:46 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_striter	*file_iterator(struct s_allocator *allocator, t_file *self,
		const char *delim)
{
	t_striter	*iter;

	iter = string_iter_create(allocator, self->buffer->buffer, delim);
	return (iter);
}
