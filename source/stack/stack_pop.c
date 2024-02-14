/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:49:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:49:40 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uintptr_t	stack_pop(t_stack *self)
{
	t_list		*node;
	uintptr_t	data;

	if (stack_is_empty(self))
		return (0);
	self->count--;
	node = list_pop_at(&self->top, 0);
	data = node->data;
	node->data = 0;
	node->next = 0;
	list_push_at(&self->freelist, node, 0);
	return (data);
}
