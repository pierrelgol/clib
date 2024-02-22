/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:32:01 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/06 11:32:01 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void	**string_split_destroy(struct s_allocator *allocator, char **split)
{
	uint64_t	i;

	i = 0;
	while (split[i])
		allocator->dealloc(allocator, split[i++]);
	allocator->dealloc(allocator, split);
	return (0);
}
