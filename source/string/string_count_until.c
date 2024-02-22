/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_count_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:31 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:21:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_count_until(const char *string, int32_t c)
{
	uint64_t	count;

	count = 0;
	while (*string != 0)
	{
		if (*string == (char)c)
			return (count);
		++count;
		++string;
	}
	return (count);
}
