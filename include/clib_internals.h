/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib_internals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/04 13:24:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIB_INTERNALS_H
# define CLIB_INTERNALS_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_mem_node	t_mem_node;
typedef struct s_allocator	t_allocator;
typedef struct s_logger		t_logger;

typedef void				*(t_fn_alloc)(void *const handle,
								const uint64_t size);
typedef void				*(t_fn_dealloc)(void *const handle,
								void *const ptr);
typedef void				*(t_fn_resize)(void *const handle, void *const ptr,
								const uint64_t nsize);
typedef void				*(t_fn_dup)(void *const handle, void *const ptr,
								const uint64_t size);
typedef void				*(t_fn_dupz)(void *const handle, void *const ptr);
typedef void				*(t_fn_deinit)(t_allocator *const allocator);
typedef void				*(t_fn_clear)(void *const handle);

struct						s_mem_node
{
	struct s_mem_node		*next;
	uint64_t				size;
	uint64_t				used;
	char					*block;
};

struct						s_logger
{
	bool					is_logging;
	bool					is_open;
	int32_t					fd;
};

struct						s_allocator
{
	void					*handle;
	t_fn_alloc				*alloc;
	t_fn_dealloc			*dealloc;
	t_fn_resize				*resize;
	t_fn_dup				*dup;
	t_fn_dupz				*dupz;
	t_fn_deinit				*deinit;
	t_fn_clear				*clear;
	t_logger				*log;
};

struct						s_gpa_allocator
{
	t_mem_node				*freelist;
	t_mem_node				*usedlist;
};

struct						s_arena_allocator
{
	uint64_t				size;
	uint64_t				used;
	char					*block;
};

#endif
