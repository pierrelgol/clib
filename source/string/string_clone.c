/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:52:49 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/10 11:52:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char *string_clone(t_allocator *const allocator, const char *source)
{
	char    *result;
	uint64_t len;
	uint64_t i;

	len = string_length(source);
	result = memalloc(allocator, len + 1);
	string_copy(result, source, len + 1);
	return (result);
}

char *string_nclone(t_allocator *const allocator, const char *source, const uint64_t n)
{
	char    *result;
	uint64_t i;

	if (!source || n == 0)
		return (string_clone(allocator, ""));
	result = memalloc(allocator, n + 1);
	i = 0;
	while (*source && i < n)
		result[i] = *source++;
	result[i] = 0x00;
	return (result);
}
