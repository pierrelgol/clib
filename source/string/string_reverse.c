/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:28:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 16:28:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	*string_reverse(char *str)
{
	uint64_t	len;
	uint64_t	i;
	char		temp;

	i = 0;
	len = string_length(str);
	if (len < 2)
		return (str);
	while (i < (len - i - 1))
	{
		temp = str[len - i - 1];
		str[len - i - 1] = str[i];
		str[i] = temp;
		++i;
	}
	return (str);
}
