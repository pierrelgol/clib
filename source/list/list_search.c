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

t_list	*list_search(struct s_list *head, uintptr_t target,
		int64_t (*f)(uintptr_t a,uintptr_t b))
{
	struct s_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->data == 0)
			current = current->next;
		if (f(current->data, target) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (0);
}
