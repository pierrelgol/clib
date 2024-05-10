/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:43 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/10 14:26:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"


uint64_t string_append_one_assume_capacity(char *dest, const char *one)
{
	uint64_t	i;
	uint64_t	j;

	if (!dest || !one)
		return (0);
	i = string_length(dest);
	j = 0;
	while (one[j])
		dest[i++] = one[j++];
	dest[i] = 0x00;
	return (j);
}

uint64_t string_append_many_assume_capacity(char *dest, const char **strings)
{
	uint64_t i;
	uint64_t j;

	if (!dest  || !strings || !*strings)
		return (0);
	i = string_length(dest);
	j = 0;
	while (strings[j])
		i += string_append_one_assume_capacity(&dest[i], strings[j++]);
	dest[i] = 0x00;
	return (i);
}

uint64_t string_append_one(t_allocator *const allocator, char **dest, const char *one, const uint64_t destsize)
{
	uint64_t	dlen;
	uint64_t	olen;

	if (!dest || !one)
		return (0);
	dlen = string_length(*dest);
	olen = string_length(one);
	if (dlen + olen + 1 < destsize)
		*dest = memresize(allocator, *dest, destsize, destsize + olen + 1);
	return (string_append_one_assume_capacity(*dest, one));
}

uint64_t string_append_many(t_allocator *const allocator, char **dest, const char **strings, const uint64_t destsize)
{
	uint64_t	i;
	uint64_t	j;

	if (!dest || !strings)
		return (0);
	i = 0;
	j= 0;
	while (strings[i])
		j += string_append_one(allocator, dest, strings[i++], destsize);
	return (j);
}
