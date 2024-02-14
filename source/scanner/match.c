/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:05:20 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:05:20 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	match(t_scanner *scanner, bool (*f)(int32_t))
{
	if (scanner->index + 1 >= scanner->size)
		return (0);
	return (f((int32_t)scanner->stream[scanner->index + 1]));
}
