/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_nclone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:00:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:00:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_nclone(struct s_allocator *allocator, const char *string,
		uint64_t n)
{
	char	*clone;

	clone = allocator->alloc(allocator, n + 1);
	clone = memory_copy(clone, string, n);
	clone[n] = 0x00;
	return (clone);
}
