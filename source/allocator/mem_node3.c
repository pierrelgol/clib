/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_node3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:39:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 14:39:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_mem_node *mem_node_remove_matching(t_mem_node **head, uintptr_t addr)
{
	t_mem_node *prev;
	t_mem_node *curr;

	if (!head || !*head || !addr)
		return (NULL);
	if (mem_node_contains_ptr((*head), addr))
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
		if (mem_node_contains_ptr(curr, addr))
			return (mem_node_remove_child(prev));
		prev = curr;
		curr = mem_node_next_or_null(curr);
	}
	return (NULL);
}

uint64_t mem_node_find_ptr_size(t_mem_node *head, uintptr_t addr)
{
	t_mem_node *curr;

	if (!head || !addr)
		return (0);
	curr = head;
	while (curr)
	{
		if (mem_node_contains_ptr(curr, addr))
			return (curr->size - curr->used);
		curr = mem_node_next_or_null(curr);
	}
	return (0);
}

void mem_node_destroy_all(t_mem_node *head)
{
	t_mem_node *temp;
	t_mem_node *curr;

	if (!head)
		return;
	curr = head;
	while (curr)
	{
		temp = curr;
		curr = mem_node_next_or_null(curr);
		mem_node_destroy(temp);
	}
}

t_mem_node	*mem_node_allocate_or_reuse(t_mem_node **head, uint64_t size)
{
	t_mem_node	*prev;
	t_mem_node	*curr;

	if (!head || !*head)
		return (mem_node_create(size));
	if (mem_node_contains_space((*head), size))
	{
		curr = (*head);
		(*head) = curr->next;
		curr->next = NULL;
		return (curr);
	}
	prev = *head;
	curr = prev->next;
	while (curr)
	{
		if (mem_node_contains_space(curr, size))
			return (mem_node_remove_child(prev));
		prev = curr;
		curr = curr->next;
	}
	return (mem_node_create(size));
}

t_mem_node *node_clear(t_mem_node *node)
{
	if (!node)
		return (NULL);
	raw_zero(node->block, node->size);
	node->next = 0;
	node->used = 0;
	return (node);
}
