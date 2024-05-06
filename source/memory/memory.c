/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:03 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 17:08:03 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void *memalloc(t_allocator *const allocator, const uint64_t size)
{
	if (!allocator)
		return (raw_alloc(size));
	return (allocator->alloc(allocator->handle, size));
}

void *memdealloc(t_allocator *const allocator, void *const ptr)
{
	if (!allocator)
		return (raw_dealloc(ptr));
	return (allocator->dealloc(allocator->handle, ptr));
}

void *memresize(t_allocator *const allocator, void *const ptr, const uint64_t osize, const uint64_t nsize)
{
	if (!allocator)
		return (raw_resize(ptr, osize, nsize));
	return (allocator->resize(allocator->handle, ptr, nsize));
}

void *memdup(t_allocator *const allocator, void *const ptr, const int64_t size)
{
	if (!allocator)
		return (raw_dup(ptr, size));
	return (allocator->dup(allocator->handle, ptr, size));
}

void *memdupz(t_allocator *const allocator, void *const ptr)
{
	if (!allocator)
		return (raw_dupz(ptr));
	return (allocator->dupz(allocator->handle, ptr));
}
