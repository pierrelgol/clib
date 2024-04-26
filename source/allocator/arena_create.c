/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:29:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:29:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_create(t_allocator *self, uint64_t size)
{
	void	*ptr;

	if ((self->used + size) > self->size)
	{
		if (self->logging)
			print(STDOUT_FILENO,"error : arena is full\n");
		return (0);
	}
	if (self->logging)
		print(STDOUT_FILENO,"arena_create(self, %lu)\n", size);
	ptr = &self->region[self->used];
	self->used += size;
	self->alloced += 1;
	return (ptr);
}
