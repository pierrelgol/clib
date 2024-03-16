/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:29:54 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/15 12:29:55 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	*arena_destroy(t_allocator *self, void *ptr)
{
	if (self->logging)
	{
		printf("arena_destroy(self, %p)\n", ptr);
		self->dealloced += 1;
	}
	return (0);
}
