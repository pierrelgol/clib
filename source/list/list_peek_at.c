/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_peek_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:00:05 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:00:07 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	*list_peek_front(t_list **list)
{
	return ((*list)->data);
}

static void	*list_peek_back(t_list **list)
{
	t_list	*curr;

	curr = (*list);
	while (curr->next)
		curr = curr->next;
	return (curr->data);
}

void	*list_peek_at(t_list **list, uint64_t index)
{
	t_list	*curr;

	if (index == 0)
		return (list_peek_front(list));
	else if (index >= list_length(*list))
		return (list_peek_back(list));
	else
	{
		curr = (*list);
		while (index--)
			curr = curr->next;
		return (curr->data);
	}
}