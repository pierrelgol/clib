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

#ifndef CLIB_H
#define CLIB_H

#include "clib_internals.h"

/******************************************************************************/
/*                                   MISC                                     */
/******************************************************************************/

void expect(bool condition);
void warn(bool condition);

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

t_allocator *arena_init(t_logger *logger, uint64_t size);
void        *arena_alloc(void *const handle, const uint64_t size);
void        *arena_dealloc(void *const handle, void *const ptr);
void *arena_resize(void *const handle, void *const ptr, const uint64_t nsize);
void *arena_dup(void *const handle, void *const ptr, const uint64_t size);
void *arena_dupz(void *const handle, void *const ptr);
void *arena_deinit(t_allocator *const allocator);

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

/******************************************************************************/
/*                                    CHAR                                    */
/******************************************************************************/

bool is_alpha(int32_t ch);
bool is_digit(int32_t ch);
bool is_spaces(int32_t ch);
bool is_blank(int32_t ch);
bool is_printable(int32_t ch);

bool is_ascii(int32_t ch);
bool is_alnum(int32_t ch);
bool is_newline(int32_t ch);
bool is_upper(int32_t ch);
bool is_lower(int32_t ch);

bool is_control(int32_t ch);
bool is_eof(int32_t ch);
bool is_graph(int32_t ch);
bool is_hex(int32_t ch);
bool is_punct(int32_t ch);

/******************************************************************************/
/*                                   BITSET                                   */
/******************************************************************************/

void bitset_set_bit(t_bitset *bitset, const uint64_t index, const bool value);
bool bitset_is_set(const t_bitset *bitset, const uint64_t index);
t_bitset bitset_init_empty(void);
t_bitset bitset_init_from_str(const char *string);
t_bitset bitset_reset(t_bitset *bitset);
t_bitset bitset_and(const t_bitset *bitset1, const t_bitset *bitset2);
t_bitset bitset_or(const t_bitset *bitset1, const t_bitset *bitset2);
t_bitset bitset_xor(const t_bitset *bitset1, const t_bitset *bitset2);
t_bitset bitset_difference(const t_bitset *bitset1, const t_bitset *bitset2);

/******************************************************************************/
/*                                   STRING                                   */
/******************************************************************************/

#define NOTFOUND 18446744073709551614UL

/* IMMUTABLE */
uint64_t string_length(const char *string);
uint64_t string_split_length(const char **split);
uint64_t string_index_of_difference(const char *s1, const char *s2);
uint64_t string_compute_replace_sequence_size(const char *haystack, const char *needle, const char *with);

int32_t string_compare(const char *s1, const char *s2);
int32_t string_ncompare(const char *s1, const char *s2, const uint64_t n);
int32_t string_casecompare(const char *s1, const char *s2);
int32_t string_ncasecompare(const char *s1, const char *s2, const uint64_t n);

uint64_t string_copy_until_scalar(char *dest, const char *src, const int32_t scalar, const uint64_t destsize);
uint64_t string_copy_until_any(char *dest, const char *src, const t_bitset *delimiters, const uint64_t destsize);
uint64_t string_copy_until_none(char *dest, const char *src, const t_bitset *delimiters, const uint64_t destsize);
uint64_t string_copy_until_predicate(char *dest, const char *src, bool(predicate)(int32_t ch), const uint64_t destsize);
uint64_t string_copy_until_sequence(char *dest, const char *src, const char *needle, const uint64_t destsize);

char *string_search_scalar(const char *source, const int32_t scalar, const uint64_t n);
char *string_search_any(const char *source, t_bitset const *delimiters, const uint64_t n);
char *string_search_none(const char *source, t_bitset const *delimiters, const uint64_t n);
char *string_search_predicate(const char *source, bool(predicate)(int32_t ch), const uint64_t n);
char *string_search_sequence(const char *haystack, const char *needle, const uint64_t n);

bool string_contains_scalar(const char *source, const int32_t scalar, const uint64_t n);
bool string_contains_any(const char *source, t_bitset const *delimiters, const uint64_t n);
bool string_contains_none(const char *source, t_bitset const *delimiters, const uint64_t n);
bool string_contains_predicate(const char *source, bool(predicate)(int32_t ch), const uint64_t n);
bool string_contains_sequence(const char *needle, const char *haystack, const uint64_t n);

bool string_starts_with_scalar(const char *source, const int32_t scalar);
bool string_starts_with_any(const char *source, t_bitset const *delimiters);
bool string_starts_with_none(const char *source, t_bitset const *delimiters);
bool string_starts_with_predicate(const char *source, bool(predicate)(int32_t ch));
bool string_starts_with_sequence(const char *haystack, const char *needle);

bool string_ends_with_scalar(const char *source, const int32_t scalar);
bool string_ends_with_any(const char *source, t_bitset const *delimiters);
bool string_ends_with_none(const char *source, t_bitset const *delimiters);
bool string_ends_with_predicate(const char *source, bool(predicate)(int32_t ch));
bool string_ends_with_sequence(const char *haystack, const char *needle);

uint64_t string_index_of_first_scalar(const char *source, const int32_t scalar);
uint64_t string_index_of_first_any(const char *source, t_bitset const *delimiters);
uint64_t string_index_of_first_none(const char *source, t_bitset const *delimiters);
uint64_t string_index_of_first_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_index_of_first_sequence(const char *haystack, const char *needle);

uint64_t string_index_of_last_scalar(const char *source, const int32_t scalar);
uint64_t string_index_of_last_any(const char *source, t_bitset const *delimiters);
uint64_t string_index_of_last_none(const char *source, t_bitset const *delimiters);
uint64_t string_index_of_last_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_index_of_last_sequence(const char *haystack, const char *needle);

uint64_t string_count_scalar(const char *source, const int32_t scalar, const uint64_t n);
uint64_t string_count_any(const char *source, t_bitset const *delimiters, const uint64_t n);
uint64_t string_count_none(const char *source, t_bitset const *delimiters, const uint64_t n);
uint64_t string_count_predicate(const char *source, bool(predicate)(int32_t ch), const uint64_t n);
uint64_t string_count_sequence(const char *haystack, const char *needle, const uint64_t n);

uint64_t string_count_until_scalar(const char *source, const int32_t scalar);
uint64_t string_count_until_any(const char *source, t_bitset const *delimiters);
uint64_t string_count_until_none(const char *source, t_bitset const *delimiters);
uint64_t string_count_until_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_count_until_sequence(const char *haystack, const char *needle);

uint64_t string_count_leading_scalar(const char *source, const int32_t scalar);
uint64_t string_count_leading_any(const char *source, t_bitset const *delimiters);
uint64_t string_count_leading_none(const char *source, t_bitset const *delimiters);
uint64_t string_count_leading_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_count_leading_sequence(const char *haystack, const char *needle);

uint64_t string_count_trailing_scalar(const char *source, const int32_t scalar);
uint64_t string_count_trailing_any(const char *source, t_bitset const *delimiters);
uint64_t string_count_trailing_none(const char *source, t_bitset const *delimiters);
uint64_t string_count_trailing_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_count_trailing_sequence(const char *haystack, const char *needle);

uint64_t string_wcount_scalar(const char *source, const int32_t scalar);
uint64_t string_wcount_any(const char *source, const t_bitset *delimiters);
uint64_t string_wcount_none(const char *source, const t_bitset *delimiters);
uint64_t string_wcount_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_wcount_sequence(const char *source, const char *sequence);

uint64_t string_wlength_scalar(const char *source, const int32_t scalar);
uint64_t string_wlength_any(const char *source, const t_bitset *delimiters);
uint64_t string_wlength_none(const char *source, const t_bitset *delimiters);
uint64_t string_wlength_predicate(const char *source, bool(predicate)(int32_t ch));
uint64_t string_wlength_sequence(const char *source, const char *sequence);

uint64_t string_wfind_scalar(const char *source, const int32_t scalar, uint64_t *out_start, uint64_t *out_end);
uint64_t string_wfind_any(const char *source, const t_bitset *delimiters, uint64_t *out_start, uint64_t *out_end);
uint64_t string_wfind_none(const char *source, const t_bitset *delimiters, uint64_t *out_start, uint64_t *out_end);
uint64_t string_wfind_predicate(const char *source, bool(predicate)(int32_t ch), uint64_t *out_start, uint64_t *out_end);
uint64_t string_wfind_sequence(const char *source, const char *needle, uint64_t *out_start, uint64_t *out_end);

/* MUTABLE */

char *string_clone(t_allocator *const allocator, const char *src);
char *string_clone_scalar(t_allocator *const allocator, const int32_t ch);
char *string_nclone(t_allocator *const allocator, const char *src, uint64_t n);

char *string_clone_until_scalar(t_allocator *const allocator, const char *src, const int32_t scalar);
char *string_clone_until_any(t_allocator *const allocator, const char *src, const t_bitset *delimiters);
char *string_clone_until_none(t_allocator *const allocator, const char *src, const t_bitset *delimiters);
char *string_clone_until_predicate(t_allocator *const allocator, const char *src, bool(predicate)(int32_t ch));
char *string_clone_until_sequence(t_allocator *const allocator, const char *src, const char *needle);

char *string_substring_scalar(t_allocator *const allocator, const char *src, const int32_t scalar);
char *string_substring_any(t_allocator *const allocator, const char *src, const t_bitset *delimiters);
char *string_substring_none(t_allocator *const allocator, const char *src, const t_bitset *delimiters);
char *string_substring_predicate(t_allocator *const allocator, const char *src, bool(predicate)(int32_t ch));
char *string_substring_sequence(t_allocator *const allocator, const char *src, const char *needle);

char *string_join_scalar(t_allocator *const allocator, const char *string, const int32_t scalar);
char *string_join_sequence(t_allocator *const allocator, const char *string, const char *sequence);
char *string_join_scalar_sequence(t_allocator *const allocator, const char *string, const int32_t scalar, const char *sequence);
char *string_join_many_sequence(t_allocator *const allocator, const char *string, const char **many);
char *string_join_many_scalar_sequence(t_allocator *const allocator, const char *string, const int32_t scalar, const char **many);

char *string_pad_left_scalar(t_allocator *const allocator, const char *string, const int32_t scalar, const uint64_t amount);
char *string_pad_right_scalar(t_allocator *const allocator, const char *string, const int32_t scalar, const uint64_t amount);
char *string_pad_left_sequence(t_allocator *const allocator, const char *string, const char *sequence, const uint64_t amount);
char *string_pad_right_sequence(t_allocator *const allocator, const char *string, const char *sequence, const uint64_t amount);

char *string_append_scalar(char *dest, const int32_t scalar, const uint64_t destsize);
char *string_append_sequence(char *dest, const char *sequence, const uint64_t destsize);
char *string_append_scalar_sequence(char *dest, const int32_t scalar, const char *sequence, const uint64_t destsize);
char *string_append_many_sequence(char *dest, const char **many, const uint64_t destsize);
char *string_append_many_scalar_sequence(char *dest, const int32_t scalar, const char **many, const uint64_t destsize);

char *string_trim_left(t_allocator *const allocator, const char *source, const uint64_t amount);
char *string_trim_right(t_allocator *const allocator, const char *source, const uint64_t amount);
char *string_trim_both(t_allocator *const allocator, const char *source, const uint64_t amount);

char *string_trim_leading_scalar(t_allocator *const allocator, const char *source, const int32_t scalar);
char *string_trim_leading_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_trim_leading_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_trim_leading_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch));
char *string_trim_leading_sequence(t_allocator *const allocator, const char *haystack, const char *needle);

char *string_trim_trailing_scalar(t_allocator *const allocator, const char *source, const int32_t scalar);
char *string_trim_trailing_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_trim_trailing_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_trim_trailing_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch));
char *string_trim_trailing_sequence(t_allocator *const allocator, const char *haystack, const char *needle);

char *string_filter_scalar(t_allocator *const allocator, const char *source, const int32_t scalar);
char *string_filter_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_filter_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char *string_filter_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch));
char *string_filter_sequence(t_allocator *const allocator, const char *haystack, const char *needle);

char *string_replace_scalar(t_allocator *const allocator, const char *source, const int32_t scalar, const int32_t with);
char *string_replace_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters, const int32_t with);
char *string_replace_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters, const int32_t with);
char *string_replace_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch), const int32_t with);
char *string_replace_sequence(const char *haystack, const char *needle, const char *with, char *out_buffer);

char **string_split_scalar(t_allocator *const allocator, const char *source, const int32_t scalar);
char **string_split_any(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char **string_split_none(t_allocator *const allocator, const char *source, t_bitset const *delimiters);
char **string_split_predicate(t_allocator *const allocator, const char *source, bool(predicate)(int32_t ch));
char **string_split_sequence(t_allocator *const allocator, const char *haystack, const char *needle);

char *string_to_reverse(char *source);
char *string_to_uppercase(char *source);
char *string_to_lowercase(char *source);
char *string_to_titlecase(char *source);
char *string_to_capitalcase(char *source);

// ***********************************+************************************** //
//                           print                                            //
// ************************************************************************** //

typedef int(t_print_fmt)(va_list arg, int fd);

typedef struct s_printer
{
	t_print_fmt *fmt;

} t_printer;

int32_t put_unumber_base(uint64_t num, const char *base, int32_t radix, int fd);
int32_t put_inumber_base(int64_t num, const char *base, int32_t radix, int fd);
int     put_char(va_list arg, int fd);
int     put_string(va_list arg, int fd);
int     put_int32(va_list arg, int fd);
int     put_ilong64(va_list arg, int fd);
int     put_ulong64(va_list arg, int fd);
int     put_uint32(va_list arg, int fd);
int     put_lowhex32(va_list arg, int fd);
int     put_upehex32(va_list arg, int fd);
int     put_ptr(va_list arg, int fd);
int     put_err(va_list arg, int fd);
t_printer print_fmt_parser(const char *fmt);
int32_t   arg_len(const char *fmt);
int32_t   print(int fd, const char *fmt, ...);

// ***********************************+************************************** //
//                           BUFFER                                           //
// ************************************************************************** //

bool      buffer_clear(t_buffer *const self);
bool      buffer_grow(t_buffer *const self);
bool      buffer_should_grow(t_buffer *const self, const uint64_t requested);
int32_t   buffer_getch(t_buffer *const self);
int32_t   buffer_putch(t_buffer *const self, const char ch);
uint64_t  buffer_reserve(t_buffer *const self, const uint64_t size);
t_buffer *buffer_create(t_allocator *const allocator);
t_buffer *buffer_destroy(t_buffer *self);
uint64_t buffer_read(t_buffer *const self, char *const buf, const uint64_t buffsize);
uint64_t buffer_cache(t_buffer *const self, const int32_t fd);
uint64_t buffer_unread_count(t_buffer *const self);
uint64_t buffer_unwrite_count(t_buffer *const self);
uint64_t buffer_write(t_buffer *const self, char *buf, const uint64_t size);
char *buffer_gets(t_buffer *const self, char *const dest, const uint64_t size);
char *buffer_puts(t_buffer *const self, const char *str);
void  buffer_compact(t_buffer *const self);
#endif
