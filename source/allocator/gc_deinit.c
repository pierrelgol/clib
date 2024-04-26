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
	t_memory_node	*node;

	node = NULL;
	node = gc_remove_front(&gc->usedlist);
	while (node)
	{
		mem_node_destroy(node);
		node = gc_remove_front(&gc->usedlist);
	}
	node = NULL;
	node = gc_remove_front(&gc->freelist);
	while (node)
	{
		mem_node_destroy(node);
		node = gc_remove_front(&gc->freelist);
	}
	memory_dealloc(gc);
	return (0);
}
