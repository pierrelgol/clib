/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:28:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:28:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_allocator	*arena_init(void)
{
	t_allocator	*arena;

	arena = memory_alloc(sizeof(t_allocator));
	arena->create = arena_create;
	arena->destroy = arena_destroy;
	arena->clear = arena_clear;
	arena->reserve = arena_reserve;
	arena->dup = arena_dup;
	arena->dupz = arena_dupz;
	arena->dupz = arena_dupz;
	arena->region = memory_zalloc(PAGE_SIZE);
	arena->size = PAGE_SIZE;
	arena->used = 0;
	return (arena);
}
