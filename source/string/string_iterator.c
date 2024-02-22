/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_iterator.c                                   :+:      :+:   :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:27:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 12:27:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"
#include <stdint.h>

char	*string_iter_next(struct s_striter *self)
{
	char	*token;

	if (self->token == 0 || self->token >= self->end)
		return (0);
	token = string_tokenize(&self->token, self->delim);
	while (string_length(token) == 0)
	{
		token = string_tokenize(&self->token, self->delim);
		if (token == 0)
			return (0);
	}
	return (token);
}

t_striter	*string_iter_create(struct s_allocator *allocator,
		const char *string, const char *delim)
{
	t_striter	*iter;

	iter = allocator->alloc(allocator, sizeof(t_striter));
	iter->allocator = allocator;
	iter->string = string_clone(allocator, string);
	iter->delim = string_clone(allocator, delim);
	iter->token = iter->string;
	iter->end = iter->string + string_length(iter->string);
	iter->next = string_iter_next;
	return (iter);
}

t_striter	*string_iter_destroy(struct s_striter *self)
{
	self->allocator->dealloc(self->allocator, self->string);
	self->allocator->dealloc(self->allocator, self->delim);
	self->allocator->dealloc(self->allocator, self);
	return (0);
}
