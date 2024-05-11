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
#define CLIB_INTERNALS_H

#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_mem_node  t_mem_node;
typedef struct s_allocator t_allocator;
typedef struct s_logger    t_logger;
typedef struct s_bitset    t_bitset;
typedef struct s_node      t_node;
typedef struct s_list      t_list;

bool(predicate)(int32_t ch);

typedef void *(t_fn_alloc) (void *const handle, const uint64_t size);
typedef void *(t_fn_dealloc) (void *const handle, void *const ptr);
typedef void *(t_fn_resize) (void *const handle, void *const ptr, const uint64_t nsize);
typedef void *(t_fn_dup) (void *const handle, void *const ptr, const uint64_t size);
typedef void *(t_fn_dupz) (void *const handle, void *const ptr);
typedef void *(t_fn_deinit) (t_allocator *const allocator);
typedef void *(t_fn_clear) (void *const handle);

struct s_mem_node
{
	struct s_mem_node *next;
	uint64_t           size;
	uint64_t           used;
	char              *block;
};

struct s_logger
{
	bool    is_logging;
	bool    is_open;
	int32_t fd;
};

struct s_allocator
{
	void         *handle;
	t_fn_alloc   *alloc;
	t_fn_dealloc *dealloc;
	t_fn_resize  *resize;
	t_fn_dup     *dup;
	t_fn_dupz    *dupz;
	t_fn_deinit  *deinit;
	t_fn_clear   *clear;
	t_logger     *log;
};

struct s_gpa_allocator
{
	t_mem_node *freelist;
	t_mem_node *usedlist;
};

struct s_arena_allocator
{
	uint64_t size;
	uint64_t used;
	char    *block;
};

#define BITSET_SIZE 256

struct s_bitset
{
	union
	{
		uint64_t set[4];
		struct
		{
			uint64_t a;
			uint64_t b;
			uint64_t c;
			uint64_t d;
		};
	};
};

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

struct s_node
{
	struct s_node *next;
	uintptr_t      data;
};

t_node *node_create(t_allocator *const allocator, const uintptr_t data);
t_node *node_destroy(t_allocator *const allocator, t_node *const node);
t_node *node_get_nchild(t_node *const node, const uint64_t n);
t_node *node_get_matching_child(t_node *const node, const uintptr_t data, bool(compare)(const uintptr_t, const uintptr_t));
t_node  *node_remove_child(t_node *const node);
uint64_t node_count_child(t_node *const node);
void     node_insert_child(t_node *const node, t_node *const child);

struct s_list
{
	t_allocator *allocator;
	t_node      *head;
	t_node      *tail;
	uint64_t     size;
};

t_list  *list_create(t_allocator *const allocator);
bool     list_is_empty(t_list *const list);
uint64_t list_size(t_list *const list);
void list_insert_at(t_list *const self, t_node *const node, const uint64_t index);
void    list_insert_back(t_list *const self, t_node *const node);
void    list_insert_front(t_list *const self, t_node *const node);
t_node *list_remove_at(t_list *const self, const uint64_t index);
t_node *list_remove_back(t_list *const self);
t_node *list_remove_front(t_list *const self);
void list_push_at(t_list *const self, const uintptr_t data, const uint64_t index);
void      list_push_back(t_list *const self, const uintptr_t data);
void      list_push_front(t_list *const self, const uintptr_t data);
uintptr_t list_pop_at(t_list *const self, const uint64_t index);
uintptr_t list_pop_back(t_list *const self);
uintptr_t list_pop_front(t_list *const self);

#endif
