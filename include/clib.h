/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:47:01 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/14 12:47:03 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIB_H
# define CLIB_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/_types.h>
# include <unistd.h>

typedef struct s_allocator	t_allocator;

typedef void				*(t_fn_create)(t_allocator *self, uint64_t size);
typedef void				*(t_fn_dup)(t_allocator *self, void *ptr,
								uint64_t size);
typedef void				*(t_fn_dupz)(t_allocator *self, void *ptr,
								uint64_t size);
typedef void				*(t_fn_destroy)(t_allocator *self, void *ptr);
typedef void				*(t_fn_clear)(t_allocator *self, void *ptr);
typedef						void(t_fn_reserve)(t_allocator *self, uint64_t size,
								uint64_t count);

typedef struct s_memory_node
{
	struct s_memory_node	*next;
	uint64_t				size;
	uint64_t				used;
	uint8_t					*block;
}							t_memory_node;

typedef struct s_allocator
{
	bool					logging;
	uint64_t				alloced;
	uint64_t				dealloced;
	uint64_t				size;
	uint64_t				used;
	uint8_t					*region;
	struct s_allocator		*parent;
	t_memory_node			*lastnode;
	t_memory_node			*usedlist;
	t_memory_node			*freelist;
	t_fn_create				*create;
	t_fn_destroy			*destroy;
	t_fn_dup				*dup;
	t_fn_dupz				*dupz;
	t_fn_clear				*clear;
	t_fn_reserve			*reserve;

}							t_allocator;

t_memory_node				*mem_node_create(t_allocator *parent, uint64_t size,
								uint64_t count);
t_memory_node				*mem_node_remove_matching(t_memory_node **head,
								uintptr_t address);
t_memory_node				*mem_node_remove_suitable(t_memory_node **head,
								uint64_t size);
t_memory_node				*mem_node_get_nchild(t_memory_node *self,
								uint64_t n);
void						mem_node_insert_child(t_memory_node *self,
								t_memory_node *child);
t_memory_node				*mem_node_remove_child(t_memory_node *self);
uint64_t					mem_node_count_child(t_memory_node *self);
t_memory_node				*mem_node_next(t_memory_node *self);
t_memory_node				*mem_node_destroy(t_memory_node *self,
								t_allocator *allocator);

t_allocator					*heap_init(void);
void						*heap_create(t_allocator *self, uint64_t size);
void						*heap_destroy(t_allocator *self, void *ptr);
void						*heap_dup(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*heap_dupz(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*heap_clear(t_allocator *self, void *ptr);
void						heap_reserve(t_allocator *self, uint64_t size,
								uint64_t count);
void						*heap_deinit(t_allocator *self);

t_allocator					*arena_init(void);
void						*arena_create(t_allocator *self, uint64_t size);
void						*arena_destroy(t_allocator *self, void *ptr);
void						*arena_dup(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*arena_dupz(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*arena_clear(t_allocator *self, void *ptr);
void						arena_reserve(t_allocator *self, uint64_t size,
								uint64_t count);
void						*arena_deinit(t_allocator *self);

t_allocator					*gc_init(void);
void						*gc_create(t_allocator *self, uint64_t size);
void						*gc_destroy(t_allocator *self, void *ptr);
void						*gc_dup(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*gc_dupz(t_allocator *self, void *ptr,
								uint64_t bytes);
void						*gc_clear(t_allocator *self, void *ptr);
void						gc_reserve(t_allocator *self, uint64_t size,
								uint64_t count);
void						*gc_deinit(t_allocator *self);

/******************************************************************************/
/*                                Bit                                         */
/******************************************************************************/

int32_t						bit_compare_bits(uint64_t num, uint64_t num2,
								uint64_t pos1, uint64_t pos2);
uint64_t					bit_bitmask_combine(uint64_t mask1, uint64_t mask2);
uint64_t					bit_bitmask_create(uint64_t start, uint64_t end);
uint64_t					bit_check_parity(uint64_t num);
uint64_t					bit_count_set_bits(uint64_t num);
uint64_t					bit_count_unset_bits(uint64_t num);
uint64_t					bit_is_set(uint64_t num, uint64_t pos);
uint64_t					bit_reverse_bits(uint64_t num);
uint64_t					bit_rotate_left(uint64_t num, uint64_t shift);
uint64_t					bit_rotate_right(uint64_t num, uint64_t shift);
uint64_t					bit_set_bit(uint64_t num, uint64_t pos);
uint64_t					bit_swap_bits(uint64_t num, uint64_t pos1,
								uint64_t pos2, uint64_t nbits);
uint64_t					bit_toggle_bit(uint64_t num, uint64_t pos);
uint64_t					bit_unset_bit(uint64_t num, uint64_t pos);

// ***********************************+************************************** //
//                                  Char                                      //
// ************************************************************************** //

/// char_is_alnum - check if a character is alphanumeric
bool						char_is_alnum(int32_t ch);

/// char_is_alpha - check if a character is alphabetic
bool						char_is_alpha(int32_t ch);

/// char_is_ascii - check if a character is ascii
bool						char_is_ascii(int32_t ch);

/// char_is_binary - check if a character is binary
bool						char_is_binary(int32_t ch);

/// char_is_decimal - check if a character is decimal
bool						char_is_decimal(int32_t ch);

/// char_is_digit - check if a character is a digit
bool						char_is_digit(int32_t ch);

/// char_is_even - check if a character is even
bool						char_is_even(int32_t ch);

/// char_is_hex - check if a character is hex
bool						char_is_hex(int32_t ch);

/// char_is_lowercase - check if a character is lowercase
bool						char_is_lowercase(int32_t ch);

/// char_is_newline - check if a character is a newline
bool						char_is_newline(int32_t ch);

/// char_is_null - check if a character is null
bool						char_is_octal(int32_t ch);

/// char_is_odd - check if a character is odd
bool						char_is_odd(int32_t ch);

/// char_is_printable - check if a character is printable
bool						char_is_printable(int32_t ch);

/// char_is_spaces - check if a character is 32 || (9-13)
bool						char_is_spaces(int32_t ch);

/// char_is_uppercase - check if a character is uppercase
bool						char_is_uppercase(int32_t ch);

/// char_is_whitespace - check if a character is whitespace (32 || (9,11,12,13))
bool						char_is_whitespace(int32_t ch);

/// char_to_lowercase - convert a character to lowercase
int32_t						char_to_lowercase(int32_t ch);

/// char_to_reversecase - convert a character to reversecase
int32_t						char_to_reversecase(int32_t ch);

/// char_to_uppercase - convert a character to uppercase
int32_t						char_to_uppercase(int32_t ch);

// ***********************************+************************************** //
//                                  Memory                                    //
// ************************************************************************** //

/// wrapper around malloc
void						*memory_alloc(uint64_t size);

/// memory_ccopy - copy memory from src to dst for n bytes or until c is found
void						*memory_ccopy(void *dst, const void *src, int32_t c,
								uint64_t n);

/// memory_compare - compare memory s1 and s2 for n bytes and return the
/// difference between the first two differing bytes or 0 if they are the same.

int32_t						memory_compare(const void *s1, const void *s2,
								uint64_t n);

/// memory_copy - copy memory from src to dst for n bytes
void						*memory_copy(void *dst, const void *src,
								uint64_t n);

/// memory_dealloc - deallocate memory (wrapper around free)
void						memory_dealloc(void *ptr);

/// memory_dup - duplicate memory from ptr for size bytes
void						*memory_dup(void *ptr, uint64_t size);

/// memory_dupz - duplicate memory from ptr for size bytes and zero the memory
void						*memory_dupz(void *ptr, uint64_t size);

/// memory_move - move memory from src to dst for n bytes (handles overlapping
/// memory)
void						*memory_move(void *dst, const void *src,
								uint64_t len);

/// memory_search - search memory for c for n bytes and return the first
/// occurrence or NULL if not found
void						*memory_search(const void *s, int32_t c,
								uint64_t n);

/// memory_set - set memory to c for len bytes
void						*memory_set(void *b, int32_t c, uint64_t len);

/// memory_zalloc - allocate memory and zero it out (wrapper around calloc)
void						*memory_zalloc(uint64_t size);

/// memory_realloc - reallocate memory from ptr for osize bytes to nsize bytes
/// (wrapper around realloc)
void						*memory_realloc(void *ptr, uint64_t osize,
								uint64_t nsize);

// ***********************************+************************************** //
//                                  String                                    //
// ************************************************************************** //
typedef struct s_striter	t_striter;

/// t_fn_stritter - function to get the next token or null
typedef char				*(t_fn_striter)(struct s_striter *self);

/// struct s_striter - string iterator structure (used to iterate over tokens in
/// a string)
struct						s_striter
{
	t_allocator				*allocator;
	char					*string;
	char					*delim;
	char					*token;
	char					*end;
	t_fn_striter			*next;
};

/// string_iter_create - create a string iterator structure to iterate over
/// tokens in a string returning the next token or NULL if no more tokens are
/// found. string_iter_create makes a copy of both string and delim so the
/// original string and delim can be deallocated after calling.
t_striter					*string_iter_create(t_allocator *allocator,
								const char *string, const char *delim);

/// string_iter_destroy - destroy a string iterator structure and deallocate any
/// memory used.
t_striter					*string_iter_destroy(struct s_striter *self);

/// string_bs - search for the first occurrence of c in string and return a
/// pointer to it or NULL if not found.
char						*string_bsearch(const char *s, int32_t c);

/// string_casecompare - compare two strings for equality ignoring case
int32_t						string_casecompare(const char *s1, const char *s2);

/// string_clone - clone a string (equivalent to strdup)
char						*string_clone(t_allocator *allocator,
								const char *string);

/// string_compare - compare two strings for equality (case sensitive)
int32_t						string_compare(const char *s1, const char *s2);

/// string_concat - concatenate two strings (equivalent to strcat)
char						*string_concat(char *s1, const char *s2);

/// strign_copy - copy a string (equivalent to strcpy)
char						*string_copy(char *dst, const char *src);

/// string_count - count the number of occurrences of c in string
/// eg. string_count("hello world", 'l') returns 3
uint64_t					string_count(const char *string, int32_t c);

/// string_cspan - count the number of characters in string that are not in
/// charset eg. string_cspan("hello world", " ") returns 5
uint64_t					string_cspan(const char *s, const char *charset);

/// string_count_leading - count the number of leading occurrences of c in
/// string eg. string_count_leading("___hello world", '_') returns 3
uint64_t					string_count_leading(const char *string, int32_t c);

/// string_count_token - count the number of tokens in string using delim as the
/// delimiter eg. string_count_token("hello world", " ") returns 2
uint64_t					string_count_token(const char *string,
								const char *delim);

/// string_count_trailing - count the number of trailing occurrences of c in
/// string eg. string_count_trailing("hello world___", '_') returns 3
uint64_t					string_count_trailing(const char *string,
								int32_t c);

/// string_count_until - count the number of characters in string until c is
/// found eg. string_count_until("hello world", ' ') returns 5
uint64_t					string_count_until(const char *string, int32_t c);

/// string_join - join two strings together and return a new string (equivalent
/// to strjoin)
char						*string_join(t_allocator *allocator, const char *s1,
								const char *s2);

/// string_lconcat - concatenate two strings (equivalent to strlcat)
uint64_t					string_lconcat(char *dst, const char *src,
								uint64_t size);

/// string_lcopy - copy a string (equivalent to strlcpy)
uint64_t					string_lcopy(char *dst, const char *src,
								uint64_t dsize);

uint64_t					string_slcopy(char *dst, const char *src,
								int32_t sentinel, uint64_t dsize);

/// string_length - return the length of a string (equivalent to strlen)
uint64_t					string_length(const char *str);

/// string_ncasecompare - compare two strings for equality ignoring case for
/// n bytes
int32_t						string_ncasecompare(const char *s1, const char *s2,
								uint64_t n);

/// string_nclone - clone a string for n bytes (equivalent to strndup)
char						*string_nclone(t_allocator *allocator,
								const char *string, uint64_t n);

/// string_ncompare - compare two strings for equality for n bytes (case
/// sensitive)
int32_t						string_ncompare(const char *s1, const char *s2,
								uint64_t n);

/// string_nconcat - concatenate two strings for n bytes (equivalent to strncat)
char						*string_nconcat(char *s1, const char *s2,
								uint64_t n);

/// string_ncopy - copy a string for n bytes (equivalent to strncpy)
char						*string_ncopy(char *dst, const char *src,
								uint64_t n);

/// string_next_token - return the length of the next token in string
/// using delim as the delimiter and copy the token to out_token /// eg.
/// string_next_token("hello world", " ", &token)
/// returns 5 and token will contain "hello"
uint64_t					string_next_token(t_allocator *allocator,
								const char *string, const char *delim,
								char **out_token);

/// string_pbrk - search for the first occurrence of any character in delim in
/// string and return a pointer to it or NULL if not found.
char						*string_pbrk(const char *s, const char *delim);

/// string_rchr - search for the last occurrence of c in string and return a
/// pointer to it or NULL if not found.
char						*string_rbsearch(const char *s, int32_t c);

/// string_reverse - reverse a string
/// eg. string_reverse("hello world") returns "dlrow olleh"
char						*string_reverse(char *str);

/// string_search - search for the first occurrence of needle in haystack and
/// return a pointer to it or NULL if not found.
char						*string_search(const char *haystack,
								const char *needle, uint64_t len);

/// string_span - count the number of characters in string that are in charset
/// eg. string_span("_____hello world", "_") returns 5
uint64_t					string_span(const char *s, const char *charset);

/// string_split - split a string using delim as the delimiter and return an
/// array of strings
char						**string_split(t_allocator *allocator,
								const char *string, const char *delim);

/// string_split_destroy - destroy an array of strings
void						**string_split_destroy(t_allocator *allocator,
								char **split);

/// string_substring - return a substring of string starting at start and of
/// length len (will truncate if len is greater than the length of the string)
char						*string_substring(t_allocator *allocator,
								char const *s, uint64_t start, uint64_t len);

/// string_tokenize - tokenize a string using delim as the delimiter and return
/// the next token by updating string (only use this function once per string,
/// use string_next_token for multiple tokens)
char						*string_tokenize(char **string, const char *delim);

/// string_tolower - convert a string to lowercase
char						*string_tolower(char *string);

/// string_toupper - convert a string to uppercase
char						*string_toupper(char *string);

// ***********************************+************************************** //
//                                  List                                      //
// ************************************************************************** //

typedef struct s_node
{
	struct s_node			*next;
	uintptr_t				data;

}							t_node;

t_node						*node_create(t_allocator *allocator,
								uintptr_t data);
t_node						*node_get_nchild(t_node *self, uint64_t n);
void						node_insert_child(t_node *self, t_node *child);
t_node						*node_remove_child(t_node *self);
uint64_t					node_count_child(t_node *self);
t_node						*node_next(t_node *self);
t_node						*node_destroy(t_node *self, t_allocator *allocator);

typedef struct s_list
{
	t_node					*head;
	t_node					*tail;
	t_allocator				*allocator;
	uint64_t				size;

}							t_list;

t_list						*list_create(t_allocator *allocator);

void						list_insert_front(t_list *self, t_node *new_head);
void						list_insert_at(t_list *self, t_node *node,
								uint64_t index);
void						list_insert_back(t_list *self, t_node *new_tail);
bool						list_is_empty(t_list *self);
uint64_t					list_size(t_list *self);
t_node						*list_remove_front(t_list *self);
t_node						*list_remove_back(t_list *self);
t_node						*list_remove_at(t_list *self, uint64_t index);
void						list_push_front(t_list *self, uintptr_t data);
void						list_push_back(t_list *self, uintptr_t data);
void						list_push_at(t_list *self, uintptr_t data,
								uint64_t index);
uintptr_t					list_pop_front(t_list *self);
uintptr_t					list_pop_back(t_list *self);
uintptr_t					list_pop_at(t_list *self, uint64_t index);

t_list						*list_destroy(t_list *self);

// ***********************************+************************************** //
//                                 Stack                                      //
// ************************************************************************** //

typedef struct s_stack
{
	uint64_t				size;
	uint64_t				count;
	t_list					*top;
	t_list					*freelist;
	t_allocator				*allocator;

}							t_stack;

/// stack_create - create a new stack and return a pointer to it
t_stack						*stack_create(t_allocator *allocator);

/// stack_destroy - destroy a stack and free all of its nodes
t_stack						*stack_destroy(t_stack *self);

/// stack_growth - grow the stack by a factor of 2
void						stack_growth(t_stack *self);

/// stack_is_empty - return true if the stack is empty
bool						stack_is_empty(t_stack *self);

/// stack_is_full - return true if the stack is full
bool						stack_is_full(t_stack *self);

/// stack_push - push data onto the stack
void						stack_push(t_stack *self, uintptr_t data);

/// stack_pop - pop data from the stack
uintptr_t					stack_pop(t_stack *self);

/// stack_peek - peek at the top of the stack
uintptr_t					stack_peek(t_stack *self);

/// stack_length - return the length of the stack
uint64_t					stack_length(t_stack *self);

/// stack_clear - clear the stack
void						stack_clear(t_stack *self);

// ***********************************+************************************** //
//                                Queue                                      //
// ************************************************************************** //

typedef struct s_queue
{
	uint64_t				size;
	uint64_t				count;
	t_list					*head;
	t_list					*tail;
	t_list					*freelist;
	t_allocator				*allocator;

}							t_queue;

/// queue_create - create a new queue and return a pointer to it
t_queue						*queue_create(t_allocator *allocator);

/// queue_destroy - destroy a queue and free all of its nodes
t_queue						*queue_destroy(t_queue *self);

/// queue_is_empty - return true if the queue is empty
bool						queue_is_empty(t_queue *self);

/// queue_is_full - return true if the queue is full
bool						queue_is_full(t_queue *self);

/// queue_enqueue - enqueue data onto the queue
void						queue_enqueue(t_queue *self, uintptr_t data);

/// queue_dequeue - dequeue data from the queue
uintptr_t					queue_dequeue(t_queue *self);

/// queue_peek - peek at the head of the queue
uintptr_t					queue_peek(t_queue *self);

/// queue_length - return the length of the queue
uint64_t					queue_length(t_queue *self);

/// queue_clear - clear the queue
void						queue_clear(t_queue *self);

/// queue_growth - grow the queue by a factor of 2
void						queue_growth(t_queue *self);

// ***********************************+************************************** //
//                               Vector                                       //
// ************************************************************************** //

typedef struct s_vector
{
	uint64_t				size;
	uint64_t				count;
	uintptr_t				*data;
	t_allocator				*allocator;

}							t_vector;

/// vector_create - create a new vector and return a pointer to it
t_vector					*vector_create(t_allocator *allocator,
								uint64_t size);

/// vector_destroy - destroy a vector
t_vector					*vector_destroy(t_vector *self);

/// vector_resize - resize the vector to new_size
void						vector_resize(t_vector *self, uint64_t new_size);

/// vector_clear - clear the vector and set the count to 0
void						vector_clear(t_vector *self);

/// vector_is_empty - return true if the vector is empty
bool						vector_is_empty(t_vector *self);

/// vector_is_full - return true if the vector is full
bool						vector_is_full(t_vector *self);

/// vector_length - return the length of the vector
uint64_t					vector_length(t_vector *self);

/// vector_push - push data onto the vector
void						vector_push(t_vector *self, uintptr_t data);

/// vector_pop - pop data from the vector
uintptr_t					vector_pop(t_vector *self);

/// vector_peek_at - peek at the index in the vector
uintptr_t					vector_peek_at(t_vector *self, uint64_t index);

/// vector_set_at - set the data at index
void						vector_set_at(t_vector *self, uintptr_t data,
								uint64_t index);

/// vector_get_at - get the data at index
uintptr_t					vector_get_at(t_vector *self, uint64_t index);

/// vector_insert_at - insert data at index
uintptr_t					vector_insert_at(t_vector *self, uintptr_t data,
								uint64_t index);

/// vector_remove_at - remove data at index
uintptr_t					vector_remove_at(t_vector *self, uint64_t index);

/// vector_sort - sort the vector using the function f to compare data
void						vector_sort(t_vector *self, int (*f)(uintptr_t d1,
									uintptr_t d2));

// ***********************************+************************************** //
//                               Buffer                                       //
// ************************************************************************** //

// equivalent to EOF
# define EOBUFF -777777
# define PAGE_SIZE 4096

typedef struct s_buffer
{
	uint64_t				bsize;
	uint64_t				r;
	uint64_t				w;
	char					ch;
	bool					is_fixed;
	char					*buffer;
	t_allocator				*allocator;

}							t_buffer;

bool						buffer_clear(t_buffer *self);
bool						buffer_grow(t_buffer *self);
bool						buffer_should_grow(t_buffer *self,
								uint32_t requested);
int32_t						buffer_getch(t_buffer *self);
int32_t						buffer_putch(t_buffer *self, char ch);
uint64_t					buffer_reserve(t_buffer *self, uint64_t size);
t_buffer					*buffer_create(t_allocator *allocator,
								uint32_t size, bool is_fixed);
t_buffer					*buffer_destroy(t_buffer *self);
uint64_t					buffer_read(t_buffer *self, char *buf,
								uint32_t size);
uint64_t					buffer_cache(t_buffer *self, int32_t fd);
uint64_t					buffer_unread_count(t_buffer *self);
uint64_t					buffer_unwrite_count(t_buffer *self);
uint64_t					buffer_write(t_buffer *self, char *buf,
								uint32_t size);
char						*buffer_gets(t_buffer *self, char *dest,
								uint32_t size);
char						*buffer_puts(t_buffer *self, char *str);
void						buffer_compact(t_buffer *self);

// ***********************************+************************************** //
//                               Scanner                                      //
// ************************************************************************** //

typedef struct s_scanner
{
	const char				*stream;
	int32_t					index;
	int32_t					size;

}							t_scanner;

t_scanner					scanner_create(const char *stream);
char						advance(t_scanner *scanner);
char						rollback(t_scanner *scanner);
char						peek(t_scanner *scanner);
char						next(t_scanner *scanner);
char						prev(t_scanner *scanner);
bool						match(t_scanner *scanner, bool (*f)(int32_t));
char						skip(t_scanner *scanner, bool (*f)(int32_t));
bool						is_eof(t_scanner *scanner);

/******************************************************************************/
/*                                Table                                       */
/******************************************************************************/

# ifndef DEFAULT_TABLE_SIZE
#  define DEFAULT_TABLE_SIZE 37781
# endif

typedef struct s_entry
{
	char					*key;
	uintptr_t				value;
}							t_entry;

typedef struct s_table
{
	uint64_t				size;
	uint64_t				capacity;
	t_entry					*body;

	t_allocator				*allocator;
}							t_table;

t_table						*table_create(t_allocator *allocator);
void						table_destroy(t_table *self);
void						table_entry_set(t_table *self, char *key,
								uintptr_t value);
uintptr_t					table_entry_get(t_table *self, char *key);
uint64_t					table_hash(char *str);
t_entry						*table_body_create(t_allocator *allocator,
								uint64_t capacity);
void						table_body_remove(t_table *self, char *key);
void						table_body_resize(t_table *self, uint64_t capacity);
uint64_t					table_body_find_empty(t_table *self, char *key);

/******************************************************************************/
/*                                file                                        */
/******************************************************************************/

# define LINE_SIZE 128

typedef struct s_file
{
	int32_t					fd;
	int32_t					mode;
	uint32_t				flag;
	uint64_t				size;
	uint64_t				pos;
	uint64_t				r;
	uint64_t				w;
	bool					is_open;
	bool					buffered_io;
	char					*path;
	char					*basename;
	t_buffer				*buffer;
	t_allocator				*allocator;

}							t_file;

t_file						*file_create(t_allocator *allocator,
								bool is_cached);
t_file						*file_destroy(t_file *self);
uint64_t					file_fsize(char *path, char *mode);
int32_t						file_mode(char *mode);
t_file						*file_get_stdout(t_allocator *allocator);
t_file						*file_get_stdin(t_allocator *allocator);
t_file						*file_get_stderr(t_allocator *allocator);
bool						file_fopen(t_file *self, char *path, char *mode);
bool						file_fclose(t_file *self);
int32_t						file_getch(t_file *self);
int32_t						file_putch(t_file *self, char ch);
char						*file_gets(t_file *self);
uint64_t					file_puts(t_file *self, char *str);
int32_t						file_read(t_file *self, char *buffer,
								uint32_t size);
int32_t						file_write(t_file *self, char *buffer,
								uint32_t size);
t_striter					*file_iterator(t_allocator *allocator, t_file *self,
								const char *delim);
t_file						*file_open_cache_all(t_allocator *allocator,
								char *path, char *mode);

// ***********************************+************************************** //
//                             string_conversion                              //
// ************************************************************************** //

char						*uint64_to_str(uint64_t n, char *str,
								uint32_t base);
char						*int64_to_str(int64_t n, char *str, uint32_t base);
uint64_t					str_to_uint64(char *str);
int64_t						str_to_int64(char *str);

// ***********************************+************************************** //
//                            misc                                            //
// ************************************************************************** //

// ***********************************+************************************** //
//                            fstack                                          //
// ************************************************************************** //

typedef struct s_fstack
{
	char					*data;
	uint32_t				size;
	uint32_t				top;
}							t_fstack;

t_fstack					fstack_create(char *data, uint32_t size);
char						fstack_push(t_fstack *self, char value);
char						fstack_pop(t_fstack *self);

// ***********************************+************************************** //
//                           fqueue                                          //
// ************************************************************************** //

typedef struct s_fqueue
{
	char					*data;
	uint32_t				size;
}							t_fqueue;

t_fqueue					fqueue_create(char *data, uint32_t size);
char						fqueue_enqueue(t_fqueue *self, char value);
char						fqueue_dequeue(t_fqueue *self);

#endif
