/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:58:34 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/04 20:58:34 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static uintptr_t list_remove_front(struct s_allocator *allocator, t_list **list)
{
	t_list   *temp;
	uintptr_t data;

	if (!*list)
		return (0);
	temp = (*list);
	data = temp->data;
	(*list) = (*list)->next;
	allocator->dealloc(allocator, temp);
	return (data);
}

static uintptr_t list_remove_back(struct s_allocator *allocator, t_list **list)
{
	t_list   *prev;
	t_list   *curr;
	uintptr_t data;

	if (!*list)
		return (0);
	curr = (*list);
	prev = curr;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	data = curr->data;
	prev->next = 0;
	allocator->dealloc(allocator, curr);
	return (data);
}

uintptr_t list_remove_at(struct s_allocator *allocator, t_list **list, uint64_t index)
{
	t_list   *prev;
	t_list   *curr;
	uintptr_t data;

	if (index == 0)
		return (list_remove_front(allocator, list));
	else if (index >= list_length(*list))
		return (list_remove_back(allocator, list));
	else
	{
		curr = (*list);
		prev = curr;
		while (index--)
		{
			prev = curr;
			curr = curr->next;
		}
		data = curr->data;
		prev->next = curr->next;
		allocator->dealloc(allocator, curr);
		return (data);
	}
}
