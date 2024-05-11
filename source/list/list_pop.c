/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:28:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:28:51 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/clib.h"

uintptr_t	list_pop_back(t_list *const self)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_back(self);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(self->allocator, node);
	return (data);
}

uintptr_t	list_pop_front(t_list *const self)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_front(self);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(self->allocator, node);
	return (data);
}

uintptr_t	list_pop_at(t_list *const self, const uint64_t index)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_at(self, index);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(self->allocator, node);
	return (data);
}
