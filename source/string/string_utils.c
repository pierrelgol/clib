/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:32:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 13:32:51 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_length(const char *string)
{
	char	*ptr;

	if (!string)
		return (0);
	ptr = (char*) string;
	while (*ptr)
		++ptr;
	return ((uint64_t)(ptr - string));
}
