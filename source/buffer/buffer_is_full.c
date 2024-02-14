/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_full.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:22:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:22:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	buffer_is_full(t_buffer *self)
{
	return (self->windex == self->size);
}
