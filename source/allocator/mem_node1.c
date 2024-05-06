/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_node1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:36:55 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 14:36:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_mem_node	*mem_node_create(uint64_t size)
{
	t_mem_node	*node;

	node = raw_alloc(sizeof(t_mem_node));
	expect(node != NULL);
	node->block = raw_alloc(size);
	node->size = size;
	node->next = NULL;
	node->used = 0;
	return (node);
}

t_mem_node	*mem_node_destroy(t_mem_node *node)
{
	if (!node)
		return (NULL);
	raw_dealloc(node->block);
	node->next = NULL;
	node->size = 0;
	node->used = 0;
	node->block = NULL;
	raw_dealloc(node);
	return (NULL);
}

t_mem_node	*mem_node_next_or_null(t_mem_node *node)
{
	if (!node || !node->next)
		return (NULL);
	return (node->next);
}

t_mem_node	*mem_node_get_nchild(t_mem_node *node, uint64_t n)
{
	t_mem_node	*temp;

	if (!node || n == 0)
		return (node);
	temp = node;
	while (n--)
	{
		if (!mem_node_next_or_null(node))
			return (temp);
		temp = mem_node_next_or_null(temp);
	}
	return (temp);
}

bool	mem_node_contains_space(t_mem_node *node, uint64_t required)
{
	if (!node)
		return (false);
	return ((node->size - node->used) >= required);
}
