/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:00:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/10 13:00:24 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_search(struct s_list *head, void *target,
		t_compare_function compare)
{
	struct s_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->data == 0)
			current = current->next;
		if (compare(current->data, target) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (0);
}
