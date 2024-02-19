/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_scanner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:57 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_scanner	file_scanner(t_file *self)
{
	return (scanner_create(self->buffer->data));
}
