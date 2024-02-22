/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	next(t_scanner *scanner)
{
	if (scanner->index + 1 >= scanner->size)
		return (0);
	return (scanner->stream[scanner->index + 1]);
}
