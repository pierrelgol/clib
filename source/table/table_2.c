/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:56:57 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/12 12:56:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	table_body_find_empty(t_table *const table, char *const key)
{
	uint64_t	index;

	index = table_hash(key) % table->capacity;
	while (table->body[index].key != NULL
		&& string_compare(table->body[index].key, key) != 0)
		index = (index + 1) % table->capacity;
	return (index);
}

void	table_body_remove(t_table *const table, char *const key)
{
	uint64_t	index;

	index = table_body_find_empty(table, key);
	if (table->body[index].key != 0)
	{
		table->body[index].key = 0;
		table->body[index].value = 0;
		table->size--;
	}
}

void	table_body_resize(t_table *const table, const uint64_t new_capacity)
{
	t_entry		*entry_old;
	uint64_t	capacity_old;
	uint64_t	i;

	entry_old = table->body;
	capacity_old = table->capacity;
	table->body = table_body_create(table->allocator, new_capacity);
	table->capacity = new_capacity;
	i = 0;
	while (i < capacity_old)
	{
		if (entry_old[i].key != NULL)
			table_entry_set(table, entry_old[i].key, entry_old[i].value);
		++i;
	}
}

uint64_t	table_hash(char *const str)
{
	unsigned long	seed;
	uint64_t		i;
	int				val;

	seed = 5381;
	i = 0;
	while (str[i])
	{
		val = str[i++];
		seed = ((seed << 5) + seed) + (unsigned long)val;
	}
	return (seed);
}
