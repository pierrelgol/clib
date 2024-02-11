/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_concat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:34:50 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:34:52 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static t_list	*list_get_head(t_list **list)
{
	return ((*list));
}

static t_list	*list_get_tail(t_list **list)
{
	t_list	*temp;

	temp = (*list);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_list	*list_concat(t_list **dlist, t_list **slist)
{
	t_list	*dtail;
	t_list	*shead;

	dtail = list_get_tail(dlist);
	shead = list_get_head(slist);
	dtail->next = shead;
	return ((*dlist));
}
