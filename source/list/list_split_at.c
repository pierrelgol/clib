/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_split_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:10:50 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 12:10:50 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list *list_split_at(t_list **list, uint64_t index)
{
	t_list *temp;
	t_list *to_return;

	if (index >= list_length(*list))
		return (0);
	if (index == 0)
	{
		temp = *list;
		*list = (*list)->next;
		temp->next = 0;
		return (temp);
	}
	temp = *list;
	while (--index)
		temp = temp->next;
	to_return = temp->next;
	temp->next = 0;
	return (to_return);
}
