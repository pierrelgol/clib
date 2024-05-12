/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:27:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:27:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	list_insert_back(t_list *self, t_node *new_tail)
{
	if (list_is_empty(self))
	{
		self->head = new_tail;
		self->tail = new_tail;
	}
	else if (self->size == 1)
	{
		self->head->next = new_tail;
		self->tail = new_tail;
	}
	else
	{
		self->tail->next = new_tail;
		self->tail = new_tail;
	}
	self->size += 1;
}

void	list_insert_front(t_list *self, t_node *new_head)
{
	if (list_is_empty(self))
	{
		self->head = new_head;
		self->tail = new_head;
	}
	else if (self->size == 1)
	{
		self->head = new_head;
		new_head->next = self->tail;
	}
	else
	{
		new_head->next = self->head;
		self->head = new_head;
	}
	self->size += 1;
}

void	list_insert_at(t_list *self, t_node *node, uint64_t index)
{
	t_node	*temp;

	if (index == 0 || list_is_empty(self))
		list_insert_front(self, node);
	else if (index >= self->size)
		list_insert_back(self, node);
	else
	{
		temp = node_get_nchild(self->head, index - 1);
		node_insert_child(temp, node);
		self->size += 1;
	}
}

