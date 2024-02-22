/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:14:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 14:14:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_next_token(struct s_allocator *allocator, const char *string,
		const char *delim, char **out_token)
{
	uint64_t	start;
	uint64_t	end;

	start = string_span(string, delim);
	end = string_cspan(&string[start], delim);
	*out_token = string_substring(allocator, string, start, end);
	return (start + end);
}
