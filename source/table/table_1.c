/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:56:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:56:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_table *table_create(struct s_allocator *const allocator)
{
	t_table *table;

	table = memalloc(allocator, sizeof(t_table));
	if (!table)
		return (NULL);
	table->allocator = allocator;
	table->size = 0;
	table->capacity = DEFAULT_TABLE_SIZE;
	table->body = table_body_create(allocator, table->capacity);
	return (table);
}

void table_destroy(t_table *const table)
{
	if (table)
	{
		if (table->body)
			memdealloc(table->allocator, table->body);
		memdealloc(table->allocator, table);
	}
}

t_entry *table_body_create(struct s_allocator *const allocator, const uint64_t capacity)
{
	return ((t_entry *) memalloc(allocator, capacity * sizeof(t_entry)));
}

uintptr_t	table_entry_get(t_table *const table, char *const key)
{
	uint64_t	index;

	index = table_body_find_empty(table, key);
	if (table->body[index].key != NULL)
		return (table->body[index].value);
	else
		return (0);
}

void	table_entry_set(t_table *const table, char *const key, const uintptr_t value)
{
	uint64_t	index;

	index = table_body_find_empty(table, key);
	if (table->body[index].key != 0)
		table->body[index].value = value;
	else
	{
		table->size++;
		if ((float)table->size / (float)table->capacity > 0.8)
		{
			table_body_resize(table, table->capacity * 2);
			index = table_body_find_empty(table, key);
		}
		table->body[index].key = key;
		table->body[index].value = value;
	}
}
