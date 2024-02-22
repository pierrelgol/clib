/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:06:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:06:18 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	skip(t_scanner *scanner, bool (*f)(int32_t))
{
	if (f(scanner->stream[scanner->index]))
		return (advance(scanner));
	return (0);
}
