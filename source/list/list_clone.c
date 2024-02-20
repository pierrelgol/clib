/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:40:06 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:40:07 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_clone(struct s_allocator *allocator, t_list *head)
{
	t_list	*temp_old;
	t_list	*new_head;
	t_list	*temp_new;
	t_list	*node;

	if (!head)
		return (0);
	new_head = list_create(allocator);
	new_head->data = head->data;
	temp_new = new_head;
	temp_old = head->next;
	while (temp_old)
	{
		node = list_create(allocator);
		node->data = temp_old->data;
		temp_new->next = node;
		temp_old = temp_old->next;
		temp_new = temp_new->next;
	}
	temp_new->next = 0;
	return (new_head);
}
