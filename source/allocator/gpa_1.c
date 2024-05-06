/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:23:54 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 17:23:55 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_allocator *gpa_init(t_logger *logger)
{
	struct s_gpa_allocator *gpa;
	t_allocator *interface;

	interface = raw_alloc(sizeof(t_allocator));
	gpa = raw_alloc(sizeof(struct s_gpa_allocator));
	gpa->freelist = NULL;
	gpa->usedlist = NULL;
	interface->handle = gpa;
	interface->log = logger;
	interface->alloc = gpa_alloc;
	interface->dealloc = gpa_dealloc;
	interface->resize = gpa_resize;
	interface->dup = gpa_dup;
	interface->dupz = gpa_dupz;
	interface->deinit = gpa_deinit;

	return (interface);
}

void *gpa_deinit(t_allocator *const allocator)
{
	struct s_gpa_allocator *handle;

	handle = (struct s_gpa_allocator *) allocator->handle;
	mem_node_destroy_all(handle->freelist);
	mem_node_destroy_all(handle->usedlist);
	raw_dealloc(allocator->handle);
	return (raw_dealloc(allocator));
}

void *gpa_alloc(void *const handle, const uint64_t size)
{
	struct s_gpa_allocator *gpa;
	t_mem_node             *node;
	void                   *ptr;

	gpa = (struct s_gpa_allocator *) handle;
	node = mem_node_allocate_or_reuse(&gpa->freelist, size);
	ptr = node->block;
	node->used = size;
	mem_node_insert_child(node, gpa->usedlist);
	gpa->usedlist = node;
	return (ptr);
}

void *gpa_dealloc(void *const handle, void *const ptr)
{
	struct s_gpa_allocator *gpa;
	t_mem_node             *node;

	gpa = (struct s_gpa_allocator *) handle;
	node = mem_node_remove_matching(&gpa->usedlist, (uintptr_t) ptr);
	node = node_clear(node);
	mem_node_insert_child(node, gpa->freelist);
	return (NULL);
}

void *gpa_resize(void *const handle, void *const ptr, const uint64_t nsize)
{
	struct s_gpa_allocator *gpa;
	void                   *result;
	uint64_t                len;

	gpa = (struct s_gpa_allocator *) handle;
	result = gpa_alloc(handle, nsize);
	len = mem_node_find_ptr_size(gpa->usedlist, (uintptr_t) ptr);
	gpa_dealloc(handle, ptr);
	return (raw_copy(result, ptr, len));
}

