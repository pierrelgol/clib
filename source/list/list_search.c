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
		int64_t (*f)(uintptr_t a, uintptr_t b))
{
	t_list	*curr;

	curr = head;
	while (curr)
	{
		if (f(curr->data, target) == 0)
			return (curr);
		curr = curr->next;
	}
	return (0);
}
