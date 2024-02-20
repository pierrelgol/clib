/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_get_stdin(struct s_allocator *allocator)
{
	t_file	*file;

	file = allocator->alloc(allocator, sizeof(t_file));
	file->fd = STDIN_FILENO;
	file->mode = O_RDONLY;
	file->is_open = true;
	file->buffer = buffer_create(allocator, PAGE_SIZE, false);
	return (file);
}
