/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:24:43 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:24:44 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_list	*list_create(t_allocator *const allocator)
{
	t_list	*list;

	list = memalloc(allocator, sizeof(t_list));
	list->allocator = allocator;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_list	*list_destroy(t_list *const self)
{
	t_node		*node;

	if (!self)
		return (0);
	while (!list_is_empty(self))
	{
		node = list_remove_front(self);
		node_destroy(self->allocator, node);
	}
	memdealloc(self->allocator, self);
	return (0);
}

bool	list_is_empty(t_list *const self)
{
	return (self->size == 0 || (!self->head && !self->tail));
}

uint64_t	list_size(t_list *const self)
{
	return (self->size);
}
