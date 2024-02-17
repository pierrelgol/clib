/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:06:52 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/04 20:06:53 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_destroy(struct s_allocator *allocator, t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		temp = allocator->dealloc(allocator, temp);
	}
	return (0);
}
