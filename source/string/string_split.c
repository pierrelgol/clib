/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:25:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:25:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	**string_split(struct s_allocator *allocator, const char *string,
		const char *delim)
{
	char		**result;
	uint64_t	size;
	uint64_t	i;
	uint64_t	j;

	size = string_count_token(string, delim);
	result = allocator->alloc(allocator, size * 8 + 8);
	i = 0;
	j = 0;
	while (i < size)
		j += string_next_token(allocator, &string[j], delim, &result[i++]);
	result[i] = NULL;
	return (result);
}
