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
# define CLIB_H

# include <assert.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ***********************************+************************************** //
//                                  Allocator                                 //
// ************************************************************************** //

struct	s_list;

struct					s_track_entry
{
	intptr_t			ptr;
	uint64_t			bytes;
};

struct	s_allocator;

typedef void			*(fn_alloc)(struct s_allocator *, uint64_t);
typedef void			*(fn_realloc)(struct s_allocator *, void *, uint64_t,
							uint64_t);
typedef void			*(fn_dealloc)(struct s_allocator *, void *);
typedef					void(fn_reserve)(struct s_allocator *, uint64_t);

# define DEFAULT_SIZE 4096

struct					s_allocator
{
	int32_t				fd;
	uint64_t			allocated;
	uint64_t			deallocated;
	uint64_t			size;
	uint64_t			count;
	uint8_t				*region;
	fn_alloc			*alloc;
	fn_realloc			*realloc;
	fn_dealloc			*dealloc;
	fn_reserve			*reserve;
	struct s_list		*next;
	struct s_list		*freelist;
	struct s_list		*refcount;
	struct s_allocator	*parent;
	struct s_allocator	*priv;
};

// ***********************************+************************************** //
//                                  heap                                      //
// ************************************************************************** //

struct s_allocator		*heap_init(void);
void					*heap_alloc(struct s_allocator *self, uint64_t size);
void					*heap_realloc(struct s_allocator *self, void *ptr,
							uint64_t osize, uint64_t nsize);
void					*heap_dealloc(struct s_allocator *self, void *ptr);
void					heap_reserve(struct s_allocator *self, uint64_t size);
struct s_allocator		*heap_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  dbg                                       //
// ************************************************************************** //

void					*dbg_allocator_alloc(struct s_allocator *self,
							uint64_t size);
struct s_allocator		*dbg_allocator_init(struct s_allocator *parent,
							bool flag);
void					*dbg_allocator_realloc(struct s_allocator *self,
							void *ptr, uint64_t osize, uint64_t nsize);
void					*dbg_allocator_dealloc(struct s_allocator *self,
							void *ptr);
void					dbg_allocator_reserve(struct s_allocator *self,
							uint64_t size);
struct s_allocator		*dbg_allocator_deinit(struct s_allocator *self);
void					dbg_allocator_sanitize(struct s_allocator *self,
							const intptr_t *ptr);

// ***********************************+************************************** //
//                                  arena                                     //
// ************************************************************************** //

struct s_allocator		*arena_allocator_init(struct s_allocator *parent,
							uint64_t size);
void					*arena_allocator_alloc(struct s_allocator *self,
							uint64_t size);
void					*arena_allocator_realloc(struct s_allocator *self,
							void *ptr, uint64_t osize, uint64_t nsize);
void					*arena_allocator_dealloc(struct s_allocator *self,
							void *ptr);
void					arena_allocator_reserve(struct s_allocator *self,
							uint64_t size);
struct s_allocator		*arena_allocator_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  Char                                      //
// ************************************************************************** //

bool					char_is_alnum(int32_t ch);
bool					char_is_alpha(int32_t ch);
bool					char_is_ascii(int32_t ch);
bool					char_is_binary(int32_t ch);
bool					char_is_decimal(int32_t ch);
bool					char_is_digit(int32_t ch);
bool					char_is_even(int32_t ch);
bool					char_is_hex(int32_t ch);
bool					char_is_lowercase(int32_t ch);
bool					char_is_newline(int32_t ch);
bool					char_is_octal(int32_t ch);
bool					char_is_odd(int32_t ch);
bool					char_is_printable(int32_t ch);
bool					char_is_spaces(int32_t ch);
bool					char_is_uppercase(int32_t ch);
bool					char_is_whitespace(int32_t ch);
int32_t					char_to_lowercase(int32_t ch);
int32_t					char_to_reversecase(int32_t ch);
int32_t					char_to_uppercase(int32_t ch);

// ***********************************+************************************** //
//                                  Memory                                    //
// ************************************************************************** //

void					*memory_alloc(uint64_t size);
void					*memory_ccopy(void *dst, const void *src, int32_t c,
							uint64_t n);
int32_t					memory_compare(const void *s1, const void *s2,
							uint64_t n);
void					*memory_copy(void *dst, const void *src, uint64_t n);
void					memory_dealloc(void *ptr);
void					*memory_dup(void *ptr, uint64_t size);
void					*memory_dupz(void *ptr, uint64_t size);
void					*memory_move(void *dst, const void *src, uint64_t len);
void					*memory_search(const void *s, int32_t c, uint64_t n);
void					*memory_set(void *b, int32_t c, uint64_t len);
void					*memory_zalloc(uint64_t size);
void					*memory_realloc(void *ptr, uint64_t osize,
							uint64_t nsize);

// ***********************************+************************************** //
//                                  String                                    //
// ************************************************************************** //

uint8_t					*string_bsearch(const uint8_t *s, int32_t c);
int32_t					string_casecompare(const uint8_t *s1,
							const uint8_t *s2);
uint8_t					*string_clone(struct s_allocator *allocator,
							const uint8_t *string);
int32_t					string_compare(const uint8_t *s1, const uint8_t *s2);
uint8_t					*string_concat(uint8_t *s1, const uint8_t *s2);
uint8_t					*string_copy(uint8_t *dst, const uint8_t *src);
uint64_t				string_count(const uint8_t *string, int32_t c);
uint64_t				string_cspan(const uint8_t *s, const uint8_t *charset);
uint64_t				string_count_leading(const uint8_t *string, int32_t c);
uint64_t				string_count_token(const uint8_t *string,
							const uint8_t *delim);
uint64_t				string_count_trailing(const uint8_t *string, int32_t c);
uint64_t				string_count_until(const uint8_t *string, int32_t c);
uint8_t					*string_join(struct s_allocator *allocator,
							const uint8_t *s1, const uint8_t *s2);
uint64_t				string_lconcat(uint8_t *dst, const uint8_t *src,
							uint64_t size);
uint64_t				string_lcopy(uint8_t *dst, const uint8_t *src,
							uint64_t dsize);
uint64_t				string_length(const uint8_t *str);
int32_t					string_ncasecompare(const uint8_t *s1,
							const uint8_t *s2, uint64_t n);
uint8_t					*string_nclone(struct s_allocator *allocator,
							const uint8_t *string, uint64_t n);
int32_t					string_ncompare(const uint8_t *s1, const uint8_t *s2,
							uint64_t n);
uint8_t					*string_nconcat(uint8_t *s1, const uint8_t *s2,
							uint64_t n);
uint8_t					*string_ncopy(uint8_t *dst, const uint8_t *src,
							uint64_t n);
uint64_t				string_next_token(struct s_allocator *allocator,
							const uint8_t *string, const uint8_t *delim,
							uint8_t **out_token);
uint8_t					*string_rbsearch(const uint8_t *s, int32_t c);
uint8_t					*string_reverse(uint8_t *str);
uint8_t					*string_search(const uint8_t *haystack,
							const uint8_t *needle, uint64_t len);
uint64_t				string_span(const uint8_t *s, const uint8_t *charset);
uint8_t					**string_split(struct s_allocator *allocator,
							const uint8_t *string, const uint8_t *delim);
void					**string_split_destroy(struct s_allocator *allocator,
							uint8_t **split);
uint8_t					*string_substring(struct s_allocator *allocator,
							uint8_t const *s, uint64_t start, uint64_t len);
uint8_t					*string_tokenize(const uint8_t **string,
							const uint8_t *delim);
uint8_t					*string_tolower(uint8_t *string);
uint8_t					*string_toupper(uint8_t *string);

// ***********************************+************************************** //
//                                  List                                      //
// ************************************************************************** //

typedef struct s_list
{
	struct s_list		*next;
	uintptr_t			data;
}						t_list;

t_list					*list_search(struct s_list *head, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));
t_list					*list_create(struct s_allocator *allocator);
t_list					*list_destroy(struct s_allocator *allocator,
							t_list *self);
t_list					*list_insert_at(struct s_allocator *allocator,
							t_list **list, uintptr_t data, uint64_t index);
t_list					*list_pop_at(t_list **self, uint64_t index);
t_list					*list_pop_first(struct s_list **head, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));
t_list					*list_push_at(t_list **self, t_list *node,
							uint64_t index);
t_list					*list_split_at(t_list **self, uint64_t index);
t_list					*list_clone(struct s_allocator *allocator,
							t_list **self);
t_list					*list_concat(t_list **dstl, t_list **srcl);
t_list					*list_rotate(t_list **list, int shift);
void					list_clear(t_list *list, uint64_t n);
uintptr_t				list_remove_at(struct s_allocator *allocator,
							t_list **list, uint64_t index);
uintptr_t				list_peek_at(t_list **list, uint64_t index);
void					list_sort(t_list **list, int (*f)(uintptr_t d1,
								uintptr_t d2));
uint64_t				list_length(t_list *list);

# define RESET "\x1B[0m"
# define BLACK "\x1B[30m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define BOLD_BLACK "\033[1m\033[30m"
# define BOLD_RED "\033[1m\033[31m"
# define BOLD_GREEN "\033[1m\033[32m"
# define BOLD_YELLOW "\033[1m\033[33m"
# define BOLD_BLUE "\033[1m\033[34m"
# define BOLD_MAGENTA "\033[1m\033[35m"
# define BOLD_CYAN "\033[1m\033[36m"
# define BOLD_WHITE "\033[1m\033[37m"

// ***********************************+************************************** //
//                                 Stack                                      //
// ************************************************************************** //

typedef struct s_stack
{
	uint64_t			size;
	uint64_t			count;
	t_list				*top;
	t_list				*freelist;
	struct s_allocator	*allocator;

}						t_stack;

t_stack					*stack_create(struct s_allocator *allocator);
t_stack					*stack_destroy(t_stack *self);
void					stack_growth(t_stack *self);
bool					stack_is_empty(t_stack *self);
bool					stack_is_full(t_stack *self);
void					stack_push(t_stack *self, uintptr_t data);
uintptr_t				stack_pop(t_stack *self);
uintptr_t				stack_peek(t_stack *self);
uint64_t				stack_length(t_stack *self);
void					stack_clear(t_stack *self);

// ***********************************+************************************** //
//                                Queue                                      //
// ************************************************************************** //

typedef struct s_queue
{
	uint64_t			size;
	uint64_t			count;
	t_list				*head;
	t_list				*tail;
	t_list				*freelist;
	struct s_allocator	*allocator;

}						t_queue;

t_queue					*queue_create(struct s_allocator *allocator);
t_queue					*queue_destroy(t_queue *self);
bool					queue_is_empty(t_queue *self);
bool					queue_is_full(t_queue *self);
void					queue_enqueue(t_queue *self, uintptr_t data);
uintptr_t				queue_dequeue(t_queue *self);
uintptr_t				queue_peek(t_queue *self);
uint64_t				queue_length(t_queue *self);
void					queue_clear(t_queue *self);
void					queue_growth(t_queue *self);

// ***********************************+************************************** //
//                               Vector                                       //
// ************************************************************************** //

typedef struct s_vector
{
	uint64_t			size;
	uint64_t			count;
	uintptr_t			*data;
	struct s_allocator	*allocator;

}						t_vector;

t_vector				*vector_create(struct s_allocator *allocator,
							uint64_t size);
t_vector				*vector_destroy(t_vector *self);
void					vector_resize(t_vector *self, uint64_t new_size);
void					vector_clear(t_vector *self);
bool					vector_is_empty(t_vector *self);
bool					vector_is_full(t_vector *self);
uint64_t				vector_length(t_vector *self);
void					vector_push(t_vector *self, uintptr_t data);
uintptr_t				vector_pop(t_vector *self);
uintptr_t				vector_peek_at(t_vector *self, uint64_t index);
void					vector_set_at(t_vector *self, uintptr_t data,
							uint64_t index);
uintptr_t				vector_get_at(t_vector *self, uint64_t index);
uintptr_t				vector_insert_at(t_vector *self, uintptr_t data,
							uint64_t index);
uintptr_t				vector_remove_at(t_vector *self, uint64_t index);
void					vector_sort(t_vector *self, int (*f)(uintptr_t d1,
								uintptr_t d2));

// ***********************************+************************************** //
//                               Buffer                                       //
// ************************************************************************** //

typedef struct s_buffer
{
	uint64_t			size;
	uint64_t			windex;
	uint64_t			rindex;
	uint8_t				*data;
	struct s_allocator	*allocator;

}						t_buffer;

t_buffer				*buffer_create(struct s_allocator *allocator,
							uint64_t size);
t_buffer				*buffer_destroy(struct s_allocator *allocator,
							t_buffer *self);
bool					buffer_is_empty(t_buffer *self);
bool					buffer_is_full(t_buffer *self);
uint8_t					buffer_read(t_buffer *self, uint8_t ch);
void					buffer_reset(t_buffer *self);
uint8_t					buffer_write(t_buffer *self, uint8_t ch);
t_buffer				*buffer_growth(t_buffer *self);
uint8_t					*buffer_ptr(t_buffer *self);

// ***********************************+************************************** //
//                               Scanner                                      //
// ************************************************************************** //

typedef struct s_scanner
{
	const uint8_t		*stream;
	int32_t				index;
	int32_t				size;

}						t_scanner;

t_scanner				scanner_create(const uint8_t *stream);
uint8_t					advance(t_scanner *scanner);
uint8_t					rollback(t_scanner *scanner);
uint8_t					peek(t_scanner *scanner);
uint8_t					next(t_scanner *scanner);
uint8_t					prev(t_scanner *scanner);
bool					match(t_scanner *scanner, bool (*f)(int32_t));
uint8_t					skip(t_scanner *scanner, bool (*f)(int32_t));
bool					is_eof(t_scanner *scanner);

/******************************************************************************/
/*                                                                            */
/*                                  Table                                     */
/*                                                                            */
/******************************************************************************/

# ifndef DEFAULT_TABLE_SIZE
#  define DEFAULT_TABLE_SIZE 37781
# endif

typedef struct s_entry
{
	uint8_t				*key;
	uintptr_t			value;
}						t_entry;

typedef struct s_table
{
	uint64_t			size;
	uint64_t			capacity;
	t_entry				*body;

	struct s_allocator	*allocator;
}						t_table;

t_table					*table_create(struct s_allocator *allocator);
void					table_destroy(t_table *self);
void					table_entry_set(t_table *self, uint8_t *key,
							uintptr_t value);
uintptr_t				table_entry_get(t_table *self, uint8_t *key);
uint64_t				table_hash(uint8_t *str);
t_entry					*table_body_create(struct s_allocator *allocator,
							uint64_t capacity);
void					table_body_remove(t_table *self, uint8_t *key);
void					table_body_resize(t_table *self, uint64_t capacity);
uint64_t				table_body_find_empty(t_table *self, uint8_t *key);

#endif
