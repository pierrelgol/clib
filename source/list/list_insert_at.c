/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_insert_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:50:39 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/04 20:50:40 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static t_list	*list_insert_front(t_list **list, t_list *new_head)
{
	new_head->next = *list;
	*list = new_head;
	return (*list);
}

static t_list	*list_insert_back(t_list **list, t_list *new_tail)
{
	t_list	*temp;

	if (!*list)
	{
		*list = new_tail;
		return (new_tail);
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_tail;
	return (*list);
}

t_list	*list_insert_at(struct s_allocator *allocator, t_list **list,
		uintptr_t data, uint64_t index)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = list_create(allocator);
	new_node->data = data;
	if (index == 0)
		return (list_insert_front(list, new_node));
	else if (index >= list_length(*list))
		return (list_insert_back(list, new_node));
	else
	{
		temp = *list;
		while (--index)
			temp = temp->next;
		new_node->next = temp->next;
		temp->next = new_node;
	}
	return (*list);
}
