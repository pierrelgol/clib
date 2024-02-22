/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:27:58 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:27:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_token(const char *string, const char *delim)
{
	uint64_t	count;

	count = 0;
	while (*string)
	{
		string += string_span(string, delim);
		if (*string != 0)
			++count;
		string += string_cspan(string, delim);
	}
	return (count);
}
