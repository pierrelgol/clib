/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rollback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:02:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 14:02:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

char	rollback(t_scanner *scanner)
{
	if ((scanner->index - 1) < 0)
		return (0);
	return (scanner->stream[--scanner->index]);
}
