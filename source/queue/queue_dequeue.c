/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_dequeue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:47:49 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:47:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uintptr_t	queue_dequeue(t_queue *self)
{
	uintptr_t	data;
	t_list		*temp;

	if (queue_is_empty(self))
		return (0);
	data = self->head->data;
	temp = list_pop_at(&self->head, 0);
	temp->next = NULL;
	temp->data = 0;
	list_push_at(&self->freelist, temp, 0);
	self->count--;
	return (data);
}
