/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:30:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:30:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	list_push_back(t_list *const self, const uintptr_t data)
{
	t_node	*node;

	node = node_create(self->allocator, data);
	list_insert_back(self, node);
}

void	list_push_front(t_list *const self, const uintptr_t data)
{
	t_node	*node;

	node = node_create(self->allocator, data);
	list_insert_front(self, node);
}

void	list_push_at(t_list *const self, const uintptr_t data, const uint64_t index)
{
	t_node	*node;

	node = node_create(self->allocator, data);
	list_insert_at(self, node, index);
}
