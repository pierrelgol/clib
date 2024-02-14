/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:21:32 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:21:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_buffer	*buffer_destroy(struct s_allocator *allocator, t_buffer *self)
{
	allocator->dealloc(allocator, self->data);
	allocator->dealloc(allocator, self);
	return (NULL);
}
