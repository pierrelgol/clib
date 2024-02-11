/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:58:01 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 10:58:02 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

struct s_allocator	*heap_init(void)
{
	struct s_allocator	*self;

	self = memory_alloc(1 * sizeof(struct s_allocator));
	self->alloc = heap_alloc;
	self->reserve = heap_reserve;
	self->dealloc = heap_dealloc;
	self->realloc = heap_realloc;
	return (self);
}
