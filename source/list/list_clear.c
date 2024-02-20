/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:07:21 by plgol.perso       #+#    #+#             */
/*   Updated: 2023/12/05 21:07:21 by plgol.perso      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	list_clear(t_list *list, uint64_t n)
{
	t_list	*temp;

	temp = list;
	while (temp && n--)
	{
		temp->data = 0;
		temp = temp->next;
	}
}
