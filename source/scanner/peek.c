/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	peek(t_scanner *scanner)
{
	if (is_eof(scanner))
		return ('\0');
	return (scanner->stream[scanner->index]);
}
