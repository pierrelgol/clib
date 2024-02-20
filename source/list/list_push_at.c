/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_puch_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:54:01 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:54:03 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static t_list	*list_push_front(t_list **list, t_list *new_head)
{
	new_head->next = *list;
	*list = new_head;
	return (*list);
}

static t_list	*list_push_back(t_list **list, t_list *new_tail)
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

t_list	*list_push_at(t_list **list, t_list *node, uint64_t index)
{
	t_list	*temp;

	if (index == 0)
		return (list_push_front(list, node));
	else if (index >= list_length(*list))
		return (list_push_back(list, node));
	else
	{
		temp = *list;
		while (--index)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
	return (*list);
}
