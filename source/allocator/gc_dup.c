/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:31:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*gc_dup(t_allocator *self, void *ptr, uint64_t bytes)
{
	void	*dup;

	dup = gc_create(self, bytes);
	if (!dup)
		return (ptr);
	memory_copy(dup, ptr, bytes);
	return (dup);
}
