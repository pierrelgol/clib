/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:05:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/10 13:05:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_pop_first(struct s_list **head, uintptr_t target,
		int64_t (*f)(uintptr_t a, uintptr_t b))
{
	struct s_list	*current;
	struct s_list	*prev;

	current = *head;
	prev = 0;
	while (current != 0)
	{
		if (current->data != 0 && f(current->data, target) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			current->next = 0;
			return (current);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
