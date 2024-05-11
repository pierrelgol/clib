/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:31:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:31:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_node	*list_remove_back(t_list *const list)
{
	t_node	*new_tail;
	t_node	*node;

	node = NULL;
	if (list_is_empty(list))
		return (NULL);
	else if (list->size == 1)
	{
		node = list->head;
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		new_tail = node_get_nchild(list->head, list_size(list) - 1);
		node = node_remove_child(new_tail);
		list->tail = new_tail;
	}
	list->size -= 1;
	return (node);
}

t_node	*list_remove_front(t_list *const list)
{
	t_node	*node;

	node = NULL;
	if (list_is_empty(list))
		return (NULL);
	else if (list->size == 1)
	{
		node = list->head;
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		node = list->head;
		list->head = node->next;
		node->next = 0;
	}
	list->size -= 1;
	return (node);
}

t_node	*list_remove_at(t_list *const list, const uint64_t index)
{
	t_node	*parent;
	t_node	*child;

	if (list_is_empty(list))
		return (NULL);
	if (index == 0)
		return (list_remove_front(list));
	if (index >= list_size(list))
		return (list_remove_back(list));
	else
	{
		parent = node_get_nchild(list->head, index - 1);
		child = node_remove_child(parent);
		list->size -= 1;
	}
	return (child);
}
