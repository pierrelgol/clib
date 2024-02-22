/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:18:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:18:52 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count(const char *string, int32_t c)
{
	uint64_t	count;

	count = 0;
	while (*string)
	{
		if (*string == (char)c)
			++count;
		++string;
	}
	return (count);
}
