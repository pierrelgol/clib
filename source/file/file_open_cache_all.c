/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_cache_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:16:25 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 13:16:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_file	*file_open_cache_all(struct s_allocator *allocator, char *path,
		char *mode)
{
	t_file		*file;
	uint64_t	size;
	uint64_t	ret;

	size = file_fsize(path, mode);
	file = file_create(allocator, true);
	file_fopen(file, path, mode);
	buffer_reserve(file->buffer, size);
	ret = (uint64_t)file_read(file, file->buffer->buffer, size);
	file->buffer->w = ret;
	file->buffer->r = 0;
	return (file);
}
