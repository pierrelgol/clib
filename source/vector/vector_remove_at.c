/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_remove_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:00:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 09:00:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uintptr_t	vector_remove_at(t_vector *self, uint64_t index)
{
	uintptr_t	*data;
	uintptr_t	value;

	if (index >= self->count)
		index = self->count;
	data = self->data;
	value = data[index];
	while (index < self->count)
	{
		data[index] = data[index + 1];
		index++;
	}
	self->count--;
	return (value);
}
