/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:33:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:33:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/clib.h"

t_node	*node_create(t_allocator *const allocator, const uintptr_t data)
{
	t_node	*node;

	node = memalloc(allocator, sizeof(t_node));
	node->next = 0;
	node->data = data;
	return (node);
}

t_node	*node_destroy(t_allocator * const allocator, t_node *const self)
{
	memdealloc(allocator, self);
	return (NULL);
}

uint64_t	node_count_child(t_node *const self)
{
	uint64_t	count;
	t_node		*child;

	if (!self || !self->next)
		return (0);
	count = 0;
	child = self;
	while (child)
	{
		child = child->next;
		++count;
	}
	return (count);
}

t_node	*node_get_nchild(t_node *const self, const uint64_t n)
{
	t_node	*temp;
	uint64_t	i;

	if (!self || n == 0)
		return (self);
	temp = self;
	i = n;
	while (i--)
	{
		if (!temp->next)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

void	node_insert_child(t_node *const self, t_node *const child)
{
	if (!self || !child)
		return ;
	child->next = self->next;
	self->next = child->next;
}
