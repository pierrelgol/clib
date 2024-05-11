/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:36:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/11 14:36:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_node	*node_remove_child(t_node *const self)
{
	t_node	*child;

	if (!self || !self->next)
		return (NULL);
	child = self->next;
	self->next = child->next;
	child->next = 0;

	return (child);
}

