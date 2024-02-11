/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_allocator_realloc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:15:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/01/30 13:15:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*logging_allocator_realloc(struct s_allocator *allocator, void *ptr,
		uint64_t old, uint64_t size)
{
	void	*new_ptr;

	new_ptr = logging_allocator_alloc(allocator, size);
	memory_copy(new_ptr, ptr, old);
	logging_allocator_dealloc(allocator, ptr);
	return (new_ptr);
}
