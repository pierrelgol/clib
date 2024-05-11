/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:44:15 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 10:44:17 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stddef.h>

void	*arena_deinit(t_allocator *const allocator)
{
	struct s_arena_allocator	*arena;

	arena = (struct s_arena_allocator *)allocator->handle;
	raw_dealloc(arena->block);
	arena->block = NULL;
	arena->size = 0;
	arena->used = 0;
	raw_dealloc(arena);
	raw_dealloc(allocator);
	return (NULL);
}

void	*arena_dup(void *const handle, void *const ptr, const uint64_t size)
{
	void	*result;

	result = arena_alloc(handle, size + _Alignof(max_align_t));
	return (raw_copy(result, ptr, size));
}

void	*arena_dupz(void *const handle, void *const ptr)
{
	void		*result;
	uint64_t	len;

	len = raw_search(ptr, 0x00, UINT64_MAX) - ptr;
	result = arena_alloc(handle, len);
	raw_ccopy(result, 0x00, ptr, len);
	return (result);
}
