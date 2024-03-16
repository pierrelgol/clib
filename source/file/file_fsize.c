/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:02:58 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:02:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	file_fsize(char *path, char *mode)
{
	t_file		file;
	uint64_t	total_size;
	uint64_t	rsize;
	char		*buffer;

	buffer = (char [PAGE_SIZE]){0};
	rsize = PAGE_SIZE;
	total_size = 0;
	if (!file_fopen(&file, path, mode))
		return (0);
	while (rsize == PAGE_SIZE)
	{
		rsize = (uint64_t)read(file.fd, buffer, PAGE_SIZE);
		total_size += rsize;
	}
	file_fclose(&file);
	return (total_size);
}
