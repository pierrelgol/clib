/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:20:57 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:20:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_buffer	*buffer_create(struct s_allocator *allocator, uint64_t size)
{
	t_buffer	*buffer;

	buffer = allocator->alloc(allocator, sizeof(t_buffer));
	buffer->allocator = allocator;
	buffer->rindex = 0;
	buffer->windex = 0;
	buffer->size = size - 1;
	buffer->data = allocator->alloc(allocator, size);
	return (buffer);
}
