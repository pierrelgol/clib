/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_dupz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:30:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:30:12 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_dupz(t_allocator *self, void *ptr, uint64_t size)
{
	void	*dup;

	dup = arena_create(self, size + 1);
	if (!dup)
		return (ptr);
	memory_copy(dup, ptr, size);
	((char *)dup)[size + 1] = 0x00;
	return (dup);
}
