/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:01:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_substring(struct s_allocator *allocator, char const *s,
		uint64_t start, uint64_t len)
{
	char		*result;
	uint64_t	slen;
	uint64_t	i;

	i = 0;
	slen = string_length(s);
	if (start > slen)
		return (string_clone(allocator, (const char *)""));
	if (len > (slen - start))
		len = slen - start;
	result = allocator->alloc(allocator, (len + 1) * sizeof(char));
	while (i < len && s[start + i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0x00;
	return (result);
}
