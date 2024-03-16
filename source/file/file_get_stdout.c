/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:01 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:02 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_get_stdout(struct s_allocator *allocator)
{
	t_file	*file;

	file = allocator->alloc(allocator, sizeof(t_file));
	file->fd = STDOUT_FILENO;
	file->mode = O_RDONLY;
	file->is_open = true;
	file->buffer = buffer_create(allocator, PAGE_SIZE, false);
	return (file);
}
