/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:42:39 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 12:42:40 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	struct s_allocator *heap;
	struct s_allocator *arena;
	struct s_allocator *logging;
	char                buffer[16384];
	uint8_t           **split;
	uint64_t            i;

	int fd;

	if (argc == 2)
	{
		heap = heap_init();
		arena = arena_allocator_init(heap, 16384);
		logging = dbg_allocator_init(arena, 0);
		fd = open(argv[1], O_RDONLY);
		read(fd, buffer, 16383);
		fd = close(fd);
		split = string_split(logging, (uint8_t *) buffer, (uint8_t *) "\n \t\v\r\f");
		i = 0;
		while (split[i])
		{
			printf("%s\n", split[i]);
			++i;
		}
		string_split_destroy(logging, split);
		dbg_allocator_deinit(logging);
		arena_allocator_deinit(arena);
		heap_deinit(heap);
		heap_deinit(heap);
	}
	return (0);
}
