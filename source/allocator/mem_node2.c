/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_node2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:38:57 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 14:39:00 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool mem_node_contains_ptr(t_mem_node *node, uintptr_t addr)
{
	if (!node)
		return (false);
	return (addr >= (uintptr_t) (node->block) && addr <= (uintptr_t) (node->block + node->size));
}

void mem_node_insert_child(t_mem_node *node, t_mem_node *child)
{
	if (!node)
		return;
	if (!child)
		node->next = child;
	else
	{
		child->next = node->next;
		node->next = child;
	}
}

t_mem_node *mem_node_remove_child(t_mem_node *node)
{
	t_mem_node *child;

	if (!node || !node->next)
		return (NULL);
	child = node->next;
	node->next = child->next;
	child->next = NULL;

	return (child);
}

uint64_t mem_node_count_child(t_mem_node *node)
{
	t_mem_node *child;
	uint64_t    count;

	if (!node || !node->next)
		return (0);
	count = 0;
	child = node;
	while (child)
	{
		child = mem_node_next_or_null(child);
		++count;
	}
	return (count);
}

t_mem_node *mem_node_remove_suitable(t_mem_node **head, uint64_t required)
{
	t_mem_node *prev;
	t_mem_node *curr;

	if (!head || !*head || !required)
		return (NULL);
	if (mem_node_contains_space((*head), required))
	{
		curr = (*head);
		(*head) = curr->next;
		curr->next = NULL;
		return (curr);
	}
	prev = (*head);
	curr = (*head)->next;
	while (curr)
	{
		if (mem_node_contains_space(curr, required))
			return (mem_node_remove_child(prev));
		prev = curr;
		curr = mem_node_next_or_null(curr);
	}
	return (NULL);
}
