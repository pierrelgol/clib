/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_deinit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:38:04 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/08 11:38:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

static void	pretty_print_region_cell(uint8_t ch)
{
	if (ch == 0x2e)
	{
		printf("%s%c%s", GREEN, '#', RESET);
	}
	else
		printf("%s%c%s", RED, "0123456789ABCDEF"[ch % 16], RESET);
}

static void	pretty_print_region(uint8_t *region, uint64_t size)
{
	uint64_t	i;
	static uint64_t	count;

	i = 0;
	printf("region :\n");
	printf("\n%p :%llu\t", &region[i],count++);
	while (i < size)
	{
		if (((i + 1) % 64) == 0)
		{
			pretty_print_region_cell(region[i]);
			printf("\n%p :\t", &region[i]);
		}
		else if (((i + 1) % 8) == 0)
		{
			pretty_print_region_cell(region[i]);
			printf("  ");
		}
		else
			pretty_print_region_cell(region[i]);
		++i;
	}
}

static void	*arena_deinit_child(struct s_allocator *parent,
		struct s_allocator *child)
{
	if (child != 0)
	{
		pretty_print_region(child->region, child->size);
		parent->dealloc(parent, child->region);
		parent->dealloc(parent, child);
	}
	return (0);
}

struct s_allocator	*arena_allocator_deinit(struct s_allocator *self)
{
	struct s_allocator	*parent;
	struct s_allocator	*child;
	struct s_list		*list;
	struct s_list		*temp;

	if (!self)
		return (0);
	parent = self->parent;
	list = self->next;
	while (list)
	{
		list = list->next;
		temp = list_pop_at(&list, 0);
		if (temp != 0)
		{
			child = temp->data;
			parent->dealloc(parent, temp);
			arena_deinit_child(parent, child);
		}
	}
	pretty_print_region(self->region, self->size);
	parent->dealloc(parent, self->region);
	return (parent->dealloc(parent, self));
}
