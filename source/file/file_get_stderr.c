/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_stderr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:28 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_get_stderr(struct s_allocator *allocator)
{
	t_file	*file;

	file = allocator->alloc(allocator, sizeof(t_file));
	file->fd = STDERR_FILENO;
	file->mode = O_RDONLY;
	file->is_open = true;
	file->buffer = buffer_create(allocator, PAGE_SIZE, false);
	return (file);
}
