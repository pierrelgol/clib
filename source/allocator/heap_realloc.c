/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:02:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:02:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*heap_realloc(struct s_allocator *self, void *ptr, uint64_t osize,
		uint64_t nsize)
{
	void	*new_ptr;

	(void)self;
	new_ptr = memory_zalloc(nsize);
	memory_copy(new_ptr, ptr, osize);
	memory_dealloc(ptr);
	return (new_ptr);
}
