/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:34:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

uint64_t	file_size(uint8_t *path, uint8_t *mode)
{
	t_file		file;
	uint64_t	size;
	uint64_t	total;
	uint8_t		buffer[512];

	if (file_open(&file, path, mode) == 0)
		return (0);
	size = sizeof(buffer) / sizeof(buffer[0]);
	total = 0;
	while (size == (sizeof(buffer) / sizeof(buffer[0])))
	{
		size = read(file.fd, buffer, sizeof(buffer) / sizeof(buffer[0]));
		total += size;
	}
	file_close(&file);
	return (total);
}
