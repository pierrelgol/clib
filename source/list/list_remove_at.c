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

uintptr_t	list_remove_at(struct s_allocator *allocator, t_list **list,
		uint64_t index)
{
	t_list		*temp;
	t_list		*to_remove;
	uintptr_t	data;

	if (index >= list_length(*list))
		return (0);
	if (index == 0)
	{
		temp = *list;
		*list = (*list)->next;
		data = temp->data;
		allocator->dealloc(allocator, temp);
		return (data);
	}
	temp = *list;
	while (--index)
		temp = temp->next;
	to_remove = temp->next;
	temp->next = to_remove->next;
	data = to_remove->data;
	allocator->dealloc(allocator, to_remove);
	return (data);
}
