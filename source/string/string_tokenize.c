/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:40:17 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 13:40:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

char	*string_tokenize(char **string, const char *delim)
{
	char	*start;
	char	*end;

	start = *string;
	if (!*start)
		return (0);
	end = string_pbrk(start, delim);
	if (end)
	{
		*end = 0;
		*string = end + 1;
	}
	else
		*string = end;
	return (start);
}
