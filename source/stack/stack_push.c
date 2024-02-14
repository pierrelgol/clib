/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:49:32 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:49:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	stack_push(t_stack *self, uintptr_t data)
{
	t_list	*node;

	if (stack_is_full(self))
		stack_growth(self);
	node = list_pop_at(&self->freelist, 0);
	node->data = data;
	self->count++;
	list_push_at(&self->top, node, 0);
}
