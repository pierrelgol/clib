/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_node_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:10:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 13:10:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_memory_node	*mem_node_destroy(t_memory_node *node, t_allocator *parent)
{
	parent->destroy(parent, node->block);
	parent->destroy(parent, node);
	return (0);
}
