/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_allocator_is_double_free.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:11:31 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/10 14:11:31 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int64_t	compare_entry(uintptr_t ptr1, uintptr_t ptr2)
{
	struct s_track_entry	*e1;
	struct s_track_entry	*e2;

	e1 = (struct s_track_entry*)ptr1;
	e2 = (struct s_track_entry*)ptr2;
	return (e1->ptr - e2->ptr);
}

struct s_list	*logging_allocator_is_double_free(struct s_allocator *self,
		const intptr_t *ptr)
{
	struct s_list			*node;
	struct s_track_entry	entry;

	entry.bytes = 0;
	entry.ptr = (intptr_t)ptr;
	node = list_search(self->freelist, (uintptr_t)&entry, compare_entry);
	if (node != 0)
		return (node);
	return (0);
}
