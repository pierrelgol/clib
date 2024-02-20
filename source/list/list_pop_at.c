/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:53:29 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:53:40 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_pop_at(t_list **list, uint64_t index)
{
	t_list	*temp;
	t_list	*to_remove;

	if (index >= list_length(*list))
		return (0);
	if (index == 0)
	{
		temp = *list;
		*list = (*list)->next;
		return (temp);
	}
	temp = *list;
	while (--index)
		temp = temp->next;
	to_remove = temp->next;
	temp->next = to_remove->next;
	return (to_remove);
}
