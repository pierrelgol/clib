/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:26:57 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/19 19:26:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/clib.h"
#include <limits.h>

int	main(int argc, char **argv)
{
	struct s_allocator *heap;
	t_file *file;
	t_buffer *b;
	uint8_t *line;


	if (argc == 2)
	{
		heap = heap_init();
		file = file_open_cache_all(heap, argv[1], "r");
		b = file->buffer;
		while ((line = file_gets(file)) != 0)
		{
			printf("%s",line);
			heap_dealloc(heap, line);
		}

		file_destroy(file);
		heap_deinit(heap);
	}
	
	return (0);
}
