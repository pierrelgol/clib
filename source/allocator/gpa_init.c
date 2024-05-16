/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/16 09:20:37 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_allocator *gc_init(void)
{
	t_allocator *gc;

	gc = memory_alloc(sizeof(t_allocator));
	gc->create = gc_create;
	gc->destroy = gc_destroy;
	gc->dup = gc_dup;
	gc->dupz = gc_dupz;
	gc->clear = gc_clear;
	gc->reserve = gc_reserve;
	gc->usedlist = NULL;
	gc->freelist = NULL;
	return (gc);
}
