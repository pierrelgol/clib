/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_seek.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:19 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	file_seek(t_file *self, uint64_t offset)
{
	self->offset = offset;
	return (self->offset);
}
