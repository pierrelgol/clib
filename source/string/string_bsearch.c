/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bsearch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:27:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:27:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_bsearch(const char *s, int32_t c)
{
	char	*ret;

	if (c == 0x00)
	{
		ret = (char *)&s[string_length(s)];
		return (ret);
	}
	else
		return (memory_search(s, c, string_length(s)));
}
