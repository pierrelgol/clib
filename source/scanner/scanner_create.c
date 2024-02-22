/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:53:27 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/14 13:53:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_scanner	scanner_create(const char *stream)
{
	t_scanner	scanner;

	scanner.stream = stream;
	scanner.index = -1;
	scanner.size = (int32_t)string_length(stream);
	return (scanner);
}
