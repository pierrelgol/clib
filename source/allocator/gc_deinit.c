/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:31:46 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static t_memory_node	*gc_remove_front(t_memory_node **head)
{
	t_memory_node	*node;

	node = NULL;
	if (!*head)
		return (NULL);
	node = (*head);
	(*head) = node->next;
	return (node);
}

void	*gc_deinit(t_allocator *gc)
{
	t_allocator		*parent;
	t_memory_node	*node;

	parent = gc->parent;
	node = NULL;
	node = gc_remove_front(&gc->usedlist);
	while (node)
	{
		mem_node_destroy(node, gc->parent);
		node = gc_remove_front(&gc->usedlist);
	}
	node = NULL;
	node = gc_remove_front(&gc->freelist);
	while (node)
	{
		mem_node_destroy(node, gc->parent);
		node = gc_remove_front(&gc->freelist);
	}
	parent->destroy(parent, gc);
	memory_dealloc(parent);
	return (0);
}
