/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:30:20 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:30:21 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_clear(t_allocator *self, void *ptr)
{
	(void)ptr;
	if (self->logging)
	{
		print(STDOUT_FILENO, "arena_clear(self, (null))\n");
	}
	memory_set(self->region, 0x00, self->used);
	self->used = 0;
	return (0);
}
