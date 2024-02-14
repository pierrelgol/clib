/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_enqueue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:47:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:47:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	queue_enqueue(t_queue *self, uintptr_t data)
{
	t_list	*node;

	if (queue_is_full(self))
		queue_growth(self);
	node = list_pop_at(&self->freelist, 0);
	node->data = data;
	node->next = NULL;
	if (queue_is_empty(self))
	{
		self->head = node;
		self->tail = node;
	}
	else
	{
		self->tail->next = node;
		self->tail = node;
	}
	self->count++;
}
