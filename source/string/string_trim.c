/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:08:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 15:08:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_trim_left(t_allocator *const allocator, const char *source,
		const uint64_t amount)
{
	uint64_t	slen;

	if (!source)
		return (NULL);
	slen = string_length(source);
	if (amount >= slen)
		return (memdupz(allocator, ""));
	return (memdupz(allocator, (void *const) & source[amount]));
}

char	*string_trim_right(t_allocator *const allocator, const char *source,
		const uint64_t amount)
{
	uint64_t	slen;
	char		*ret;

	if (!source)
		return (NULL);
	slen = string_length(source);
	if (amount >= slen)
		return (memdupz(allocator, ""));
	ret = memalloc(allocator, slen - amount + 1);
	if (!ret)
		return (NULL);
	raw_copy(ret, source, slen - amount);
	ret[slen - amount] = '\0';
	return (ret);
}

char	*string_trim_both(t_allocator *const allocator, const char *source,
		const uint64_t amount)
{
	uint64_t	trim_both_amount;
	uint64_t	slen;
	char		*ret;

	if (!source)
		return (NULL);
	slen = string_length(source);
	if (amount >= slen)
		return (memdupz(allocator, ""));
	trim_both_amount = amount * 2;
	if (trim_both_amount >= slen)
		return (memdupz(allocator, ""));
	ret = memalloc(allocator, slen - trim_both_amount + 1);
	if (!ret)
		return (NULL);
	raw_copy(ret, &source[amount], slen - trim_both_amount);
	ret[slen - trim_both_amount] = '\0';
	return (ret);
}
