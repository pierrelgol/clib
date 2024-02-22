/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:45:29 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:45:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stddef.h>

uint64_t	string_length(const char *str)
{
	const char	*ptr;

	if (!str)
		return (0);
	ptr = str;
	while (*ptr)
		++ptr;
	return (ptr - str);
}
