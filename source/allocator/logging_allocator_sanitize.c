/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_allocator_sanitize.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:10:32 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/10 14:10:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdarg.h>

void	logging_allocator_sanitize(struct s_allocator *self, const intptr_t *ptr)
{
	struct s_track_entry	*entry;
	t_list					*node;

	node = logging_allocator_is_double_free(self, ptr);
	if (node != 0)
	{
		entry = (struct s_track_entry*)node->data;
		dprintf(self->fd, "[double free ][ptr: @%p][size: %llu][Err ]\n}\n",
			(void *)entry->ptr, entry->bytes);
		exit(0);
	}
}
