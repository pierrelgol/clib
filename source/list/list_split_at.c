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

t_list	*list_split_at(t_list **list, uint64_t index)
{
	t_list	*ret;
	t_list	*tmp;

	if (index >= list_length(*list))
		return (0);
	if (index == 0)
	{
		tmp = *list;
		*list = (*list)->next;
		tmp->next = 0;
		return (tmp);
	}
	tmp = *list;
	while (--index)
	{
		tmp = tmp->next;
	}
	ret = tmp->next;
	tmp->next = 0;
	return (ret);
}
