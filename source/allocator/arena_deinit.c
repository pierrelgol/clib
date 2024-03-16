/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_deinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:46:21 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:46:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_deinit(t_allocator *self)
{
	if (self->logging)
	{
		printf("arena_create was called  : %llu times\n", self->alloced);
		printf("arena_destroy was called : %llu times\n", self->dealloced);
		printf("total allocation         : %llu bytes\n", self->size);
	}
	free(self->region);
	free(self);
	return (0);
}
