/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:21:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 08:21:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	buffer_is_empty(t_buffer *self)
{
	return (self->rindex == self->windex);
}
