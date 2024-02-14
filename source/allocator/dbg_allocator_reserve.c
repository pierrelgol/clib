/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_allocator_reserve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:35:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 13:35:40 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	dbg_allocator_reserve(struct s_allocator *self, uint64_t size)
{
	self->parent->reserve(self->parent, size);
}
