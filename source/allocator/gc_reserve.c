/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_reserve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:31:40 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	gc_insert_front(t_memory_node **head, t_memory_node *node)
{
	if (!*head)
	{
		*head = node;
		return ;
	}
	else
	{
		node->next = (*head);
		(*head) = node;
	}
}

void	gc_reserve(t_allocator *self, uint64_t size, uint64_t count)
{
	t_memory_node	*node;

	node = mem_node_create(self->parent, size, count);
	gc_insert_front(&self->freelist, node);
}
