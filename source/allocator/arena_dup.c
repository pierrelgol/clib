/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:30:04 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:30:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_dup(t_allocator *self, void *ptr, uint64_t size)
{
	void	*dup;

	dup = arena_create(self, size);
	if (!dup)
		return (ptr);
	memory_copy(dup, ptr, size);
	return (dup);
}
