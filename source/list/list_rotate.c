/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:18:18 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/12 10:18:18 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static unsigned int	_shift_abs(int v)
{
	if (v < 0)
		return ((unsigned int)-v);
	return ((unsigned int)v);
}

static t_list	*list_rotate_left(t_list **list, unsigned int shift)
{
	uint64_t	length;
	t_list		*temp;

	length = list_length(*list);
	shift %= length;
	if (shift == 0)
		return (*list);
	while (shift--)
	{
		temp = list_pop_at(list, 0);
		list_push_at(list, temp, length);
	}
	return (*list);
}

static t_list	*list_rotate_right(t_list **list, unsigned int shift)
{
	uint64_t	length;
	t_list		*temp;

	length = list_length(*list);
	shift %= length;
	if (shift == 0)
		return (*list);
	while (shift--)
	{
		temp = list_pop_at(list, length);
		list_push_at(list, temp, 0);
	}
	return (*list);
}

t_list	*list_rotate(t_list **list, int shift)
{
	unsigned int	r;

	r = _shift_abs(shift);
	if (shift == 0)
		return (*list);
	else if (shift < 0)
		return (list_rotate_left(list, r));
	else
		return (list_rotate_right(list, r));
}
