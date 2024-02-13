/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:14:30 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 10:14:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIB_H
#define CLIB_H

#include <assert.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ***********************************+************************************** //
//                                  Allocator                                 //
// ************************************************************************** //

struct s_list;

struct s_track_entry
{
	intptr_t ptr;
	uint64_t bytes;
};

struct s_allocator;

typedef void *(fn_alloc) (struct s_allocator *, uint64_t);
typedef void *(fn_realloc) (struct s_allocator *, void *, uint64_t, uint64_t);
typedef void *(fn_dealloc) (struct s_allocator *, void *);
typedef void(fn_reserve)(struct s_allocator *, uint64_t);

#define DEFAULT_SIZE 4096

struct s_allocator
{
	int32_t             fd;
	uint64_t            allocated;
	uint64_t            deallocated;
	uint64_t            size;
	uint64_t            count;
	uint8_t            *region;
	fn_alloc           *alloc;
	fn_realloc         *realloc;
	fn_dealloc         *dealloc;
	fn_reserve         *reserve;
	struct s_list      *next;
	struct s_list      *freelist;
	struct s_list      *refcount;
	struct s_allocator *parent;
	struct s_allocator *priv;
};

// ***********************************+************************************** //
//                                  heap                                      //
// ************************************************************************** //

struct s_allocator *heap_init(void);
void               *heap_alloc(struct s_allocator *self, uint64_t size);
void *heap_realloc(struct s_allocator *self, void *ptr, uint64_t osize, uint64_t nsize);
void               *heap_dealloc(struct s_allocator *self, void *ptr);
void                heap_reserve(struct s_allocator *self, uint64_t size);
struct s_allocator *heap_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  logging                                   //
// ************************************************************************** //

struct s_allocator *logging_allocator_init(struct s_allocator *parent, bool do_flog);
void *logging_allocator_alloc(struct s_allocator *self, uint64_t size);
void *logging_allocator_realloc(struct s_allocator *self, void *ptr, uint64_t osize, uint64_t nsize);
void *logging_allocator_dealloc(struct s_allocator *self, void *ptr);
void  logging_allocator_reserve(struct s_allocator *self, uint64_t size);
struct s_allocator *logging_allocator_deinit(struct s_allocator *self);
struct s_list *logging_allocator_is_double_free(struct s_allocator *self, const intptr_t *ptr);
void logging_allocator_sanitize(struct s_allocator *self, const intptr_t *ptr);

// ***********************************+************************************** //
//                                  arena                                     //
// ************************************************************************** //

struct s_allocator *arena_allocator_init(struct s_allocator *parent, uint64_t size);
void *arena_allocator_alloc(struct s_allocator *self, uint64_t size);
void *arena_allocator_realloc(struct s_allocator *self, void *ptr, uint64_t osize, uint64_t nsize);
void *arena_allocator_dealloc(struct s_allocator *self, void *ptr);
void  arena_allocator_reserve(struct s_allocator *self, uint64_t size);
struct s_allocator *arena_allocator_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  Char                                      //
// ************************************************************************** //

bool    char_is_alnum(int32_t ch);
bool    char_is_alpha(int32_t ch);
bool    char_is_ascii(int32_t ch);
bool    char_is_binary(int32_t ch);
bool    char_is_decimal(int32_t ch);
bool    char_is_digit(int32_t ch);
bool    char_is_even(int32_t ch);
bool    char_is_hex(int32_t ch);
bool    char_is_lowercase(int32_t ch);
bool    char_is_newline(int32_t ch);
bool    char_is_octal(int32_t ch);
bool    char_is_odd(int32_t ch);
bool    char_is_printable(int32_t ch);
bool    char_is_spaces(int32_t ch);
bool    char_is_uppercase(int32_t ch);
bool    char_is_whitespace(int32_t ch);
int32_t char_to_lowercase(int32_t ch);
int32_t char_to_reversecase(int32_t ch);
int32_t char_to_uppercase(int32_t ch);

// ***********************************+************************************** //
//                                  Memory                                    //
// ************************************************************************** //

void   *memory_alloc(uint64_t size);
void   *memory_ccopy(void *dst, const void *src, int32_t c, uint64_t n);
int32_t memory_compare(const void *s1, const void *s2, uint64_t n);
void   *memory_copy(void *dst, const void *src, uint64_t n);
void    memory_dealloc(void *ptr);
void   *memory_dup(void *ptr, uint64_t size);
void   *memory_dupz(void *ptr, uint64_t size);
void   *memory_move(void *dst, const void *src, uint64_t len);
void   *memory_search(const void *s, int32_t c, uint64_t n);
void   *memory_set(void *b, int32_t c, uint64_t len);
void   *memory_zalloc(uint64_t size);
void   *memory_realloc(void *ptr, uint64_t osize, uint64_t nsize);

// ***********************************+************************************** //
//                                  String                                    //
// ************************************************************************** //

uint8_t *string_bsearch(const uint8_t *s, int32_t c);
int32_t  string_casecompare(const uint8_t *s1, const uint8_t *s2);
uint8_t *string_clone(struct s_allocator *allocator, const uint8_t *string);
int32_t  string_compare(const uint8_t *s1, const uint8_t *s2);
uint8_t *string_concat(uint8_t *s1, const uint8_t *s2);
uint8_t *string_copy(uint8_t *dst, const uint8_t *src);
uint64_t string_count(const uint8_t *string, int32_t c);
uint64_t string_cspan(const uint8_t *s, const uint8_t *charset);
uint64_t string_count_leading(const uint8_t *string, int32_t c);
uint64_t string_count_token(const uint8_t *string, const uint8_t *delim);
uint64_t string_count_trailing(const uint8_t *string, int32_t c);
uint64_t string_count_until(const uint8_t *string, int32_t c);
uint8_t *string_join(struct s_allocator *allocator, const uint8_t *s1, const uint8_t *s2);
uint64_t string_lconcat(uint8_t *dst, const uint8_t *src, uint64_t size);
uint64_t string_lcopy(uint8_t *dst, const uint8_t *src, uint64_t dsize);
uint64_t string_length(const uint8_t *str);
int32_t  string_ncasecompare(const uint8_t *s1, const uint8_t *s2, uint64_t n);
uint8_t *string_nclone(struct s_allocator *allocator, const uint8_t *string, uint64_t n);
int32_t  string_ncompare(const uint8_t *s1, const uint8_t *s2, uint64_t n);
uint8_t *string_nconcat(uint8_t *s1, const uint8_t *s2, uint64_t n);
uint8_t *string_ncopy(uint8_t *dst, const uint8_t *src, uint64_t n);
uint64_t string_next_token(struct s_allocator *allocator, const uint8_t *string, const uint8_t *delim, uint8_t **out_token);

uint8_t *string_rbsearch(const uint8_t *s, int32_t c);
uint8_t *string_reverse(uint8_t *str);
uint8_t *string_search(const uint8_t *haystack, const uint8_t *needle, uint64_t len);
uint64_t string_span(const uint8_t *s, const uint8_t *charset);
uint8_t **string_split(struct s_allocator *allocator, const uint8_t *string, const uint8_t *delim);
void **string_split_destroy(struct s_allocator *allocator, uint8_t **split);
uint8_t *string_substring(struct s_allocator *allocator, uint8_t const *s, uint64_t start, uint64_t len);
uint8_t *string_tokenize(const uint8_t **string, const uint8_t *delim);
uint8_t *string_tolower(uint8_t *string);
uint8_t *string_toupper(uint8_t *string);

// ***********************************+************************************** //
//                                  List                                      //
// ************************************************************************** //

typedef int64_t (*t_compare_function)(uintptr_t, uintptr_t);

struct s_list
{
	struct s_list *next;
	uintptr_t      data;
};

typedef struct s_list t_list;

t_list *list_search(struct s_list *head, uintptr_t target, t_compare_function compare);
t_list *list_create(struct s_allocator *allocator);
t_list *list_destroy(struct s_allocator *allocator, t_list *self);
t_list *list_insert_at(struct s_allocator *allocator, t_list **list, uintptr_t data, uint64_t index);

t_list *list_pop_at(t_list **self, uint64_t index);
t_list *list_pop_first(struct s_list **head, uintptr_t target, t_compare_function compare);
t_list *list_push_at(t_list **self, t_list *node, uint64_t index);
t_list *list_split_at(t_list **self, uint64_t index);
t_list *list_clone(struct s_allocator *allocator, t_list **self);
t_list *list_concat(t_list **dstl, t_list **srcl);
t_list *list_rotate(t_list **list, int shift);
void    list_clear(t_list *list, uint64_t n);
uintptr_t list_remove_at(struct s_allocator *allocator, t_list **list, uint64_t index);
uintptr_t list_peek_at(t_list **list, uint64_t index);
void	list_sort(t_list **list, int (*f)(uintptr_t d1, uintptr_t d2));
uint64_t  list_length(t_list *list);


#define RESET "\x1B[0m"
#define BLACK "\x1B[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define BOLD_BLACK "\033[1m\033[30m"
#define BOLD_RED "\033[1m\033[31m"
#define BOLD_GREEN "\033[1m\033[32m"
#define BOLD_YELLOW "\033[1m\033[33m"
#define BOLD_BLUE "\033[1m\033[34m"
#define BOLD_MAGENTA "\033[1m\033[35m"
#define BOLD_CYAN "\033[1m\033[36m"
#define BOLD_WHITE "\033[1m\033[37m"

#endif
