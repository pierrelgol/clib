/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count_leading.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:22:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:22:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_leading(const char *string, int32_t c)
{
	uint64_t	count;

	count = 0;
	while (*string && *string == (char)c)
	{
		++count;
		++string;
	}
	return (count);
}
