/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:40:06 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 11:40:07 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	list_count(t_list *list, uintptr_t target, int64_t (*f)(uintptr_t a,
			uintptr_t b))
{
	uint64_t	i;

	i = 0;
	while (list)
	{
		if (f(list->data, target) == 0)
			i++;
		list = list->next;
	}
	return (i);
}
