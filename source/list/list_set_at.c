/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_set_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:40:06 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:40:07 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_set_at(t_list **self, uintptr_t data, uint64_t index)
{
	t_list	*curr;

	curr = *self;
	if (index == 0)
	{
		curr->data = data;
	}
	else if (index >= list_length(*self))
	{
		while (curr->next)
			curr = curr->next;
		curr->data = data;
	}
	else
	{
		while (index--)
			curr = curr->next;
		curr->data = data;
	}
	return (*self);
}
