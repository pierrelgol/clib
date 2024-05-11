/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:44:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 10:44:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_allocator	*arena_init(t_logger *logger, uint64_t size)
{
	struct s_arena_allocator	*arena;
	t_allocator					*interface;

	interface = raw_alloc(sizeof(struct s_allocator));
	arena = raw_alloc(sizeof(struct s_arena_allocator));
	arena->block = raw_alloc(size + 32);
	arena->size = size;
	arena->used = 0;
	interface->handle = arena;
	interface->alloc = arena_alloc;
	interface->dealloc = arena_dealloc;
	interface->dup = arena_dup;
	interface->dupz = arena_dupz;
	interface->resize = arena_resize;
	interface->deinit = arena_deinit;
	interface->log = logger;
	return (interface);
}

void	*arena_alloc(void *const handle, const size_t size)
{
	struct s_arena_allocator	*arena;
	void						*ptr;

	arena = (struct s_arena_allocator *)handle;
	if ((arena->used + size) > arena->size)
		return (NULL);
	ptr = (arena->block + arena->used);
	arena->used += size;
	return (ptr);
}

void	*arena_dealloc(void *const handle, void *const ptr)
{
	(void)handle;
	(void)ptr;
	return (NULL);
}

void	*arena_resize(void *const handle, void *const ptr, const uint64_t nsize)
{
	void	*result;

	result = arena_alloc(handle, nsize);
	result = raw_ccopy(result, 0x00, ptr, nsize);
	return (result);
}
