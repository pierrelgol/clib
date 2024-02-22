/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count_trailing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:23:13 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:23:13 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_trailing(const char *string, int32_t c)
{
	uint64_t	count;
	uint64_t	len;

	count = 0;
	len = string_length(string);
	while (len >= 1 && string[len - 1] == (char)c)
	{
		++count;
		--len;
	}
	return (count);
}
