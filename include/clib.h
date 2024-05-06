/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:23:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/04 13:23:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIB_H__
#define __CLIB_H__

#include "clib_internals.h"

/******************************************************************************/
/*                                   MISC                                     */
/******************************************************************************/

void expect(bool condition);

/******************************************************************************/
/*                                 ALLOCATOR                                  */
/******************************************************************************/

t_allocator *gpa_init(t_logger *logger);

void *gpa_alloc(void *const handle, const uint64_t size);
void *gpa_dealloc(void *const handle, void *const ptr);
void *gpa_resize(void *const handle, void *const ptr, const uint64_t nsize);
void *gpa_dup(void *const handle, void *const ptr, const uint64_t size);
void *gpa_dupz(void *const handle, void *const ptr);
void *gpa_deinit(t_allocator *const allocator);

t_mem_node *mem_node_create(uint64_t size);
t_mem_node *mem_node_destroy(t_mem_node *node);
t_mem_node *mem_node_get_nchild(t_mem_node *node, uint64_t n);
t_mem_node *mem_node_next_or_null(t_mem_node *node);
bool        mem_node_contains_space(t_mem_node *node, uint64_t required);
bool        mem_node_contains_ptr(t_mem_node *node, uintptr_t addr);
void        mem_node_insert_child(t_mem_node *node, t_mem_node *child);
t_mem_node *mem_node_remove_child(t_mem_node *node);
uint64_t    mem_node_count_child(t_mem_node *node);
t_mem_node *mem_node_remove_suitable(t_mem_node **head, uint64_t required);
t_mem_node *mem_node_remove_matching(t_mem_node **head, uintptr_t addr);
void        mem_node_destroy_all(t_mem_node *head);
t_mem_node *node_clear(t_mem_node *node);
t_mem_node *mem_node_allocate_or_reuse(t_mem_node **head, uint64_t size);
uint64_t    mem_node_find_ptr_size(t_mem_node *head, uintptr_t addr);

/******************************************************************************/
/*                                 RAW_MEMORY                                 */
/******************************************************************************/

void *raw_alloc(const uint64_t size);
void *raw_dealloc(void *const ptr);
void *raw_resize(void *const ptr, const uint64_t osize, const uint64_t nsize);
void *raw_dup(const void *ptr, const int64_t size);
void *raw_dupz(const void *ptr);
void *raw_copy(void *const dst, const void *src, const uint64_t dstsize);
void *raw_ccopy(void *const dst, const int32_t byte, const void *src, const uint64_t dstsize);
void   *raw_fill(void *const dst, const int32_t byte, const uint64_t dstsize);
void   *raw_zero(void *const dst, const uint64_t dstsize);
void   *raw_search(const void *s, const int32_t byte, const uint64_t dstsize);
void   *raw_move(void *dst, const void *src, const uint64_t len);
int32_t raw_compare(const void *a, const void *b, const uint64_t size);

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/

void *memalloc(t_allocator *const allocator, const uint64_t size);
void *memdealloc(t_allocator *const allocator, void *const ptr);
void *memresize(t_allocator *const allocator, void *const ptr, const uint64_t osize, const uint64_t nsize);
void *memdup(t_allocator *const allocator, void *const ptr, const int64_t size);
void *memdupz(t_allocator *const allocator, void *const ptr);

#endif
