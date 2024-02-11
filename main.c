/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:35:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/10 13:35:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/clib.h"

int main(void)
{
	struct s_allocator *heap;
	struct s_allocator *arena;
	uint8_t            *str = (uint8_t *) "This is a string";
	uint8_t            *res;

	heap = heap_init();
	arena = arena_allocator_init(heap, 65536);
	int i = 0;
	while (i < 10000)
	{
		res = string_clone(arena, str);
		++i;
	}
	printf("%s",res);
	arena_allocator_deinit(arena);
	heap_deinit(heap);
	return (0);
}
