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
//                                  Allocator                                 //
// ************************************************************************** //

struct	s_list;

struct					s_track_entry
{
	intptr_t			ptr;
	uint64_t			bytes;
};

struct	s_allocator;

typedef void			*(t_fn_alloc)(struct s_allocator *, uint64_t);
typedef void			*(t_fn_realloc)(struct s_allocator *, void *, uint64_t,
							uint64_t);
typedef void			*(t_fn_dealloc)(struct s_allocator *, void *);
typedef					void(t_fn_reserve)(struct s_allocator *, uint64_t);

# define DEFAULT_SIZE 4096

/*
	struct s_allocator  {
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
*/
struct					s_allocator
{
	int32_t				fd;
	uint64_t			allocated;
	uint64_t			deallocated;
	uint64_t			size;
	uint64_t			count;
	uint8_t				*region;
	t_fn_alloc			*alloc;
	t_fn_realloc		*realloc;
	t_fn_dealloc		*dealloc;
	t_fn_reserve		*reserve;
	struct s_list		*next;
	struct s_list		*freelist;
	struct s_list		*refcount;
	struct s_allocator	*parent;
	struct s_allocator	*priv;
};

// ***********************************+************************************** //
//                                  heap                                      //
// ************************************************************************** //

/// heap_init - initialize the heap allocator
/// thin wrapper around malloc/free/realloc
struct s_allocator		*heap_init(void);

/// heap_alloc - allocate memory from the heap
void					*heap_alloc(struct s_allocator *self, uint64_t size);

/// heap_realloc - reallocate memory from the heap
void					*heap_realloc(struct s_allocator *self, void *ptr,
							uint64_t osize, uint64_t nsize);

/// heap_dealloc - deallocate memory from the heap
void					*heap_dealloc(struct s_allocator *self, void *ptr);

/// heap_reserve - reserve memory from the heap (does nothing for heap
/// allocator)
void					heap_reserve(struct s_allocator *self, uint64_t size);

/// heap_deinit - deinitialize the heap allocator
struct s_allocator		*heap_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  dbg                                       //
// ************************************************************************** //

/// dbg_allocator_init - initialize the debug allocator
/// this allocator will track all allocations and deallocations from the parent
/// allocator flag is used to enable/disable printing of allocation/deallocation
/// information to stdout 0 = enabled, 1 = to a file
struct s_allocator		*dbg_allocator_init(struct s_allocator *parent,
							bool flag);

/// dbg_allocator_alloc - allocate memory from the debug allocator (pass through
/// to parent)
void					*dbg_allocator_alloc(struct s_allocator *self,
							uint64_t size);

/// dbg_allocator_realloc - reallocate memory from the debug allocator (pass
/// through to parent)
void					*dbg_allocator_realloc(struct s_allocator *self,
							void *ptr, uint64_t osize, uint64_t nsize);

//// dbg_allocator_dealloc - deallocate memory from the debug allocator (pass
/// through to parent)
void					*dbg_allocator_dealloc(struct s_allocator *self,
							void *ptr);

/// dbg_allocator_reserve - reserve memory from the debug allocator (pass
/// through to parent)
void					dbg_allocator_reserve(struct s_allocator *self,
							uint64_t size);

/// dbg_allocator_deinit - deinitialize the debug allocator
struct s_allocator		*dbg_allocator_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  arena                                     //
// ************************************************************************** //

/// arena_allocator_init - initialize the arena allocator
/// this allocator will allocate a large region of memory and then allocate from
/// that region.  It will not free memory until the entire region is deallocated
/// this is useful for allocating many small objects that will be deallocated
/// all at once. The arena allocator will allocate a new arena when the current
/// one is full and will chain them together.
struct s_allocator		*arena_allocator_init(struct s_allocator *parent,
							uint64_t size);

/// arena_allocator_alloc - allocate memory from the arena allocator
void					*arena_allocator_alloc(struct s_allocator *self,
							uint64_t size);

/// arena_allocator_realloc - reallocate memory from the arena allocator
void					*arena_allocator_realloc(struct s_allocator *self,
							void *ptr, uint64_t osize, uint64_t nsize);

/// arena_allocator_dealloc - deallocate memory from the arena allocator
void					*arena_allocator_dealloc(struct s_allocator *self,
							void *ptr);

/// arena_allocator_reserve - reserve memory from the arena allocator (use when
/// you know you will need more memory in the future) this function is essential
/// to call if you want to allocate a split of strings or other objects that can
/// cross the arena boundary
void					arena_allocator_reserve(struct s_allocator *self,
							uint64_t size);

/// arena_allocator_deinit - deinitialize the arena allocator
struct s_allocator		*arena_allocator_deinit(struct s_allocator *self);

// ***********************************+************************************** //
//                                  Char                                      //
// ************************************************************************** //

/// char_is_alnum - check if a character is alphanumeric
bool					char_is_alnum(int32_t ch);

/// char_is_alpha - check if a character is alphabetic
bool					char_is_alpha(int32_t ch);

/// char_is_ascii - check if a character is ascii
bool					char_is_ascii(int32_t ch);

/// char_is_binary - check if a character is binary
bool					char_is_binary(int32_t ch);

/// char_is_decimal - check if a character is decimal
bool					char_is_decimal(int32_t ch);

/// char_is_digit - check if a character is a digit
bool					char_is_digit(int32_t ch);

/// char_is_even - check if a character is even
bool					char_is_even(int32_t ch);

/// char_is_hex - check if a character is hex
bool					char_is_hex(int32_t ch);

/// char_is_lowercase - check if a character is lowercase
bool					char_is_lowercase(int32_t ch);

/// char_is_newline - check if a character is a newline
bool					char_is_newline(int32_t ch);

/// char_is_null - check if a character is null
bool					char_is_octal(int32_t ch);

/// char_is_odd - check if a character is odd
bool					char_is_odd(int32_t ch);

/// char_is_printable - check if a character is printable
bool					char_is_printable(int32_t ch);

/// char_is_spaces - check if a character is 32 || (9-13)
bool					char_is_spaces(int32_t ch);

/// char_is_uppercase - check if a character is uppercase
bool					char_is_uppercase(int32_t ch);

/// char_is_whitespace - check if a character is whitespace (32 || (9,11,12,13))
bool					char_is_whitespace(int32_t ch);

/// char_to_lowercase - convert a character to lowercase
int32_t					char_to_lowercase(int32_t ch);

/// char_to_reversecase - convert a character to reversecase
int32_t					char_to_reversecase(int32_t ch);

/// char_to_uppercase - convert a character to uppercase
int32_t					char_to_uppercase(int32_t ch);

// ***********************************+************************************** //
//                                  Memory                                    //
// ************************************************************************** //

/// wrapper around malloc
void					*memory_alloc(uint64_t size);

/// memory_ccopy - copy memory from src to dst for n bytes or until c is found
void					*memory_ccopy(void *dst, const void *src, int32_t c,
							uint64_t n);

/// memory_compare - compare memory s1 and s2 for n bytes and return the
/// difference between the first two differing bytes or 0 if they are the same.

int32_t					memory_compare(const void *s1, const void *s2,
							uint64_t n);

/// memory_copy - copy memory from src to dst for n bytes
void					*memory_copy(void *dst, const void *src, uint64_t n);

/// memory_dealloc - deallocate memory (wrapper around free)
void					memory_dealloc(void *ptr);

/// memory_dup - duplicate memory from ptr for size bytes
void					*memory_dup(void *ptr, uint64_t size);

/// memory_dupz - duplicate memory from ptr for size bytes and zero the memory
void					*memory_dupz(void *ptr, uint64_t size);

/// memory_move - move memory from src to dst for n bytes (handles overlapping
/// memory)
void					*memory_move(void *dst, const void *src, uint64_t len);

/// memory_search - search memory for c for n bytes and return the first
/// occurrence or NULL if not found
void					*memory_search(const void *s, int32_t c, uint64_t n);

/// memory_set - set memory to c for len bytes
void					*memory_set(void *b, int32_t c, uint64_t len);

/// memory_zalloc - allocate memory and zero it out (wrapper around calloc)
void					*memory_zalloc(uint64_t size);

/// memory_realloc - reallocate memory from ptr for osize bytes to nsize bytes
/// (wrapper around realloc)
void					*memory_realloc(void *ptr, uint64_t osize,
							uint64_t nsize);

// ***********************************+************************************** //
//                                  String                                    //
// ************************************************************************** //
struct	s_striter;

///t_fn_stritter - function to get the next token or null
typedef	uint8_t			*(t_fn_striter)(struct s_striter *self);

/// struct s_striter - string iterator structure (used to iterate over tokens in
/// a string)
typedef struct s_striter
{
	struct s_allocator	*allocator;
	uint8_t				*string;
	uint8_t				*delim;
	uint8_t				*token;
	uint8_t				*end;
	t_fn_striter		*next;
}						t_striter;

/// string_iter_create - create a string iterator structure to iterate over
/// tokens in a string returning the next token or NULL if no more tokens are
/// found. string_iter_create makes a copy of both string and delim so the
/// original string and delim can be deallocated after calling.
t_striter				*string_iter_create(struct s_allocator *allocator,
							const uint8_t *string, const uint8_t *delim);

/// string_iter_destroy - destroy a string iterator structure and deallocate any
/// memory used.
t_striter				*string_iter_destroy(struct s_striter *self);

/// string_bs - search for the first occurrence of c in string and return a
/// pointer to it or NULL if not found.
uint8_t					*string_bsearch(const uint8_t *s, int32_t c);

/// string_casecompare - compare two strings for equality ignoring case
int32_t					string_casecompare(const uint8_t *s1,
							const uint8_t *s2);

/// string_clone - clone a string (equivalent to strdup)
uint8_t					*string_clone(struct s_allocator *allocator,
							const uint8_t *string);

/// string_compare - compare two strings for equality (case sensitive)
int32_t					string_compare(const uint8_t *s1, const uint8_t *s2);

/// string_concat - concatenate two strings (equivalent to strcat)
uint8_t					*string_concat(uint8_t *s1, const uint8_t *s2);

/// strign_copy - copy a string (equivalent to strcpy)
uint8_t					*string_copy(uint8_t *dst, const uint8_t *src);

/// string_count - count the number of occurrences of c in string
/// eg. string_count("hello world", 'l') returns 3
uint64_t				string_count(const uint8_t *string, int32_t c);

/// string_cspan - count the number of characters in string that are not in
/// charset eg. string_cspan("hello world", " ") returns 5
uint64_t				string_cspan(const uint8_t *s, const uint8_t *charset);

/// string_count_leading - count the number of leading occurrences of c in
/// string eg. string_count_leading("___hello world", '_') returns 3
uint64_t				string_count_leading(const uint8_t *string, int32_t c);

/// string_count_token - count the number of tokens in string using delim as the
/// delimiter eg. string_count_token("hello world", " ") returns 2
uint64_t				string_count_token(const uint8_t *string,
							const uint8_t *delim);

/// string_count_trailing - count the number of trailing occurrences of c in
/// string eg. string_count_trailing("hello world___", '_') returns 3
uint64_t				string_count_trailing(const uint8_t *string, int32_t c);

/// string_count_until - count the number of characters in string until c is
/// found eg. string_count_until("hello world", ' ') returns 5
uint64_t				string_count_until(const uint8_t *string, int32_t c);

/// string_join - join two strings together and return a new string (equivalent
/// to strjoin)
uint8_t					*string_join(struct s_allocator *allocator,
							const uint8_t *s1, const uint8_t *s2);

/// string_lconcat - concatenate two strings (equivalent to strlcat)
uint64_t				string_lconcat(uint8_t *dst, const uint8_t *src,
							uint64_t size);

/// string_lcopy - copy a string (equivalent to strlcpy)
uint64_t				string_lcopy(uint8_t *dst, const uint8_t *src,
							uint64_t dsize);

uint64_t				string_slcopy(uint8_t *dst, const uint8_t *src,
							int32_t sentinel, uint64_t dsize);

/// string_length - return the length of a string (equivalent to strlen)
uint64_t				string_length(const uint8_t *str);

/// string_ncasecompare - compare two strings for equality ignoring case for
/// n bytes
int32_t					string_ncasecompare(const uint8_t *s1,
							const uint8_t *s2, uint64_t n);

/// string_nclone - clone a string for n bytes (equivalent to strndup)
uint8_t					*string_nclone(struct s_allocator *allocator,
							const uint8_t *string, uint64_t n);

/// string_ncompare - compare two strings for equality for n bytes (case
/// sensitive)
int32_t					string_ncompare(const uint8_t *s1, const uint8_t *s2,
							uint64_t n);

/// string_nconcat - concatenate two strings for n bytes (equivalent to strncat)
uint8_t					*string_nconcat(uint8_t *s1, const uint8_t *s2,
							uint64_t n);

/// string_ncopy - copy a string for n bytes (equivalent to strncpy)
uint8_t					*string_ncopy(uint8_t *dst, const uint8_t *src,
							uint64_t n);

/// string_next_token - return the length of the next token in string
/// using delim as the delimiter and copy the token to out_token /// eg.
/// string_next_token("hello world", " ", &token)
/// returns 5 and token will contain "hello"
uint64_t				string_next_token(struct s_allocator *allocator,
							const uint8_t *string, const uint8_t *delim,
							uint8_t **out_token);

/// string_pbrk - search for the first occurrence of any character in delim in
/// string and return a pointer to it or NULL if not found.
uint8_t					*string_pbrk(const uint8_t *s, const uint8_t *delim);

/// string_rchr - search for the last occurrence of c in string and return a
/// pointer to it or NULL if not found.
uint8_t					*string_rbsearch(const uint8_t *s, int32_t c);

/// string_reverse - reverse a string
/// eg. string_reverse("hello world") returns "dlrow olleh"
uint8_t					*string_reverse(uint8_t *str);

/// string_search - search for the first occurrence of needle in haystack and
/// return a pointer to it or NULL if not found.
uint8_t					*string_search(const uint8_t *haystack,
							const uint8_t *needle, uint64_t len);

/// string_span - count the number of characters in string that are in charset
/// eg. string_span("_____hello world", "_") returns 5
uint64_t				string_span(const uint8_t *s, const uint8_t *charset);

/// string_split - split a string using delim as the delimiter and return an
/// array of strings
uint8_t					**string_split(struct s_allocator *allocator,
							const uint8_t *string, const uint8_t *delim);

/// string_split_destroy - destroy an array of strings
void					**string_split_destroy(struct s_allocator *allocator,
							uint8_t **split);

/// string_substring - return a substring of string starting at start and of
/// length len (will truncate if len is greater than the length of the string)
uint8_t					*string_substring(struct s_allocator *allocator,
							uint8_t const *s, uint64_t start, uint64_t len);

/// string_tokenize - tokenize a string using delim as the delimiter and return
/// the next token by updating string (only use this function once per string,
/// use string_next_token for multiple tokens)
uint8_t					*string_tokenize(uint8_t **string,
							const uint8_t *delim);

/// string_tolower - convert a string to lowercase
uint8_t					*string_tolower(uint8_t *string);

/// string_toupper - convert a string to uppercase
uint8_t					*string_toupper(uint8_t *string);

// ***********************************+************************************** //
//                                  List                                      //
// ************************************************************************** //

typedef struct s_list
{
	struct s_list		*next;
	uintptr_t			data;
}						t_list;

/// list_clear - clear n nodes from the list (if n is greater than the length of
/// the list, the entire list will be cleared)
void					list_clear(t_list *list, uint64_t n);

/// list_search - search for a node in the list using a custom comparison
/// function and return a pointer to it or NULL if not found.
t_list					*list_search(struct s_list *head, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));

/// list_create - create a new list and return a pointer to it
t_list					*list_create(struct s_allocator *allocator);

/// list_destroy - destroy a list and free all of its nodes
t_list					*list_destroy(struct s_allocator *allocator,
							t_list *self);

/// list_insert_at - insert a new node at index in the list and return a pointer
/// to it safe to use even if the list is empty
t_list					*list_insert_at(struct s_allocator *allocator,
							t_list **list, uintptr_t data, uint64_t index);

/// list_pop_at - remove a node at index from the list and return a pointer to
/// it (caller is responsible for freeing the node)

t_list					*list_pop_at(t_list **self, uint64_t index);

/// list_pop_first - remove the first node from the list and return a pointer to
/// it (caller is responsible for freeing the node)
t_list					*list_pop_first(struct s_list **head, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));

/// list_push - push the provided node to the specified index in the list and
/// return a pointer to the list head
t_list					*list_push_at(t_list **self, t_list *node,
							uint64_t index);

/// list_split_at - split the list at index and return a pointer to the new list
t_list					*list_split_at(t_list **self, uint64_t index);

/// list_clone - clone a list and return a pointer to the new list (deep copy)
t_list					*list_clone(struct s_allocator *allocator,
							t_list *head);

/// list_concat - concatenate two lists and return a pointer to the new list
t_list					*list_concat(t_list **dstl, t_list **srcl);

/// list_rotate - rotate the list by shift and return a pointer to the new list
/// (positive shift rotates right, negative shift rotates left)
t_list					*list_rotate(t_list **list, int shift);

/// list_remove_at - remove a node at index from the list and return its data
/// (all references to the node will be invalidated)
uintptr_t				list_remove_at(struct s_allocator *allocator,
							t_list **list, uint64_t index);

/// list_peek_at - return the data of the node at index in the list
uintptr_t				list_peek_at(t_list **list, uint64_t index);

/// list_sort - sort the list using a custom comparison function (merge sort
/// fast pointer slow pointer algorithm)
void					list_sort(t_list **list, int (*f)(uintptr_t d1,
								uintptr_t d2));

/// list_length - return the length of the list
uint64_t				list_length(t_list *list);

/// list_index_of - return the index of the first occurrence of target in the
/// list using a custom comparison function
uint64_t				list_index_of(t_list *list, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));

/// list_count - return the number of occurrences of target in the list using a
/// custom comparison function
uint64_t				list_count(t_list *list, uintptr_t target,
							int64_t (*f)(uintptr_t a, uintptr_t b));

/// list_set_at - set the data of the node at index in the list and return a
/// pointer to the list head
t_list					*list_set_at(t_list **self, uintptr_t data,
							uint64_t index);

/// list_get_at - get a pointer to the node at index in the list
t_list					*list_get_at(t_list **self, uint64_t index);

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

/// stack_create - create a new stack and return a pointer to it
t_stack					*stack_create(struct s_allocator *allocator);

/// stack_destroy - destroy a stack and free all of its nodes
t_stack					*stack_destroy(t_stack *self);

/// stack_growth - grow the stack by a factor of 2
void					stack_growth(t_stack *self);

/// stack_is_empty - return true if the stack is empty
bool					stack_is_empty(t_stack *self);

/// stack_is_full - return true if the stack is full
bool					stack_is_full(t_stack *self);

/// stack_push - push data onto the stack
void					stack_push(t_stack *self, uintptr_t data);

/// stack_pop - pop data from the stack
uintptr_t				stack_pop(t_stack *self);

/// stack_peek - peek at the top of the stack
uintptr_t				stack_peek(t_stack *self);

/// stack_length - return the length of the stack
uint64_t				stack_length(t_stack *self);

/// stack_clear - clear the stack
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

/// queue_create - create a new queue and return a pointer to it
t_queue					*queue_create(struct s_allocator *allocator);

/// queue_destroy - destroy a queue and free all of its nodes
t_queue					*queue_destroy(t_queue *self);

/// queue_is_empty - return true if the queue is empty
bool					queue_is_empty(t_queue *self);

/// queue_is_full - return true if the queue is full
bool					queue_is_full(t_queue *self);

/// queue_enqueue - enqueue data onto the queue
void					queue_enqueue(t_queue *self, uintptr_t data);

/// queue_dequeue - dequeue data from the queue
uintptr_t				queue_dequeue(t_queue *self);

/// queue_peek - peek at the head of the queue
uintptr_t				queue_peek(t_queue *self);

/// queue_length - return the length of the queue
uint64_t				queue_length(t_queue *self);

/// queue_clear - clear the queue
void					queue_clear(t_queue *self);

/// queue_growth - grow the queue by a factor of 2
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

/// vector_create - create a new vector and return a pointer to it
t_vector				*vector_create(struct s_allocator *allocator,
							uint64_t size);

/// vector_destroy - destroy a vector
t_vector				*vector_destroy(t_vector *self);

/// vector_resize - resize the vector to new_size
void					vector_resize(t_vector *self, uint64_t new_size);

/// vector_clear - clear the vector and set the count to 0
void					vector_clear(t_vector *self);

/// vector_is_empty - return true if the vector is empty
bool					vector_is_empty(t_vector *self);

/// vector_is_full - return true if the vector is full
bool					vector_is_full(t_vector *self);

/// vector_length - return the length of the vector
uint64_t				vector_length(t_vector *self);

/// vector_push - push data onto the vector
void					vector_push(t_vector *self, uintptr_t data);

/// vector_pop - pop data from the vector
uintptr_t				vector_pop(t_vector *self);

/// vector_peek_at - peek at the index in the vector
uintptr_t				vector_peek_at(t_vector *self, uint64_t index);

/// vector_set_at - set the data at index
void					vector_set_at(t_vector *self, uintptr_t data,
							uint64_t index);

/// vector_get_at - get the data at index
uintptr_t				vector_get_at(t_vector *self, uint64_t index);

/// vector_insert_at - insert data at index
uintptr_t				vector_insert_at(t_vector *self, uintptr_t data,
							uint64_t index);

/// vector_remove_at - remove data at index
uintptr_t				vector_remove_at(t_vector *self, uint64_t index);

/// vector_sort - sort the vector using the function f to compare data
void					vector_sort(t_vector *self, int (*f)(uintptr_t d1,
								uintptr_t d2));

// ***********************************+************************************** //
//                               Buffer                                       //
// ************************************************************************** //

// equivalent to EOF
# define EOBUFF -777777
# define PAGE_SIZE 4096

typedef struct s_buffer
{
	uint64_t			bsize;
	uint64_t			r;
	uint64_t			w;
	uint8_t				ch;
	bool				is_fixed;
	uint8_t				*buffer;
	struct s_allocator	*allocator;

}						t_buffer;

bool					buffer_clear(t_buffer *self);
bool					buffer_grow(t_buffer *self);
bool					buffer_should_grow(t_buffer *self, uint32_t requested);
int32_t					buffer_getch(t_buffer *self);
int32_t					buffer_putch(t_buffer *self, uint8_t ch);
uint64_t				buffer_reserve(t_buffer *self, uint64_t size);
t_buffer				*buffer_create(struct s_allocator *allocator,
							uint32_t size, bool is_fixed);
t_buffer				*buffer_destroy(t_buffer *self);
uint64_t				buffer_read(t_buffer *self, uint8_t *buf,
							uint32_t size);
uint64_t				buffer_cache(t_buffer *self, int32_t fd);
uint64_t				buffer_unread_count(t_buffer *self);
uint64_t				buffer_unwrite_count(t_buffer *self);
uint64_t				buffer_write(t_buffer *self, uint8_t *buf,
							uint32_t size);
uint8_t					*buffer_gets(t_buffer *self, uint8_t *dest,
							uint32_t size);
uint8_t					*buffer_puts(t_buffer *self, uint8_t *str);
void					buffer_compact(t_buffer *self);

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
/*                                Table                                       */
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

/******************************************************************************/
/*                                file                                        */
/******************************************************************************/

# define LINE_SIZE 128

typedef struct s_file
{
	int32_t				fd;
	int32_t				mode;
	uint32_t			flag;
	uint64_t			size;
	uint64_t			pos;
	uint64_t			r;
	uint64_t			w;
	bool				is_open;
	bool				buffered_io;
	uint8_t				*path;
	uint8_t				*basename;
	t_buffer			*buffer;
	struct s_allocator	*allocator;

}						t_file;

t_file					*file_create(struct s_allocator *allocator,
							bool is_cached);
t_file					*file_destroy(t_file *self);
uint64_t				file_fsize(char *path, char *mode);
int32_t					file_mode(char *mode);
t_file					*file_get_stdout(struct s_allocator *allocator);
t_file					*file_get_stdin(struct s_allocator *allocator);
t_file					*file_get_stderr(struct s_allocator *allocator);
bool					file_fopen(t_file *self, char *path, char *mode);
bool					file_fclose(t_file *self);
int32_t					file_getch(t_file *self);
int32_t					file_putch(t_file *self, uint8_t ch);
uint8_t					*file_gets(t_file *self);
uint32_t				file_puts(t_file *self, uint8_t *str);
int32_t					file_read(t_file *self, uint8_t *buffer, uint32_t size);
int32_t					file_write(t_file *self, uint8_t *buffer,
							uint32_t size);
t_striter				*file_iterator(struct s_allocator *allocator,
							t_file *self, const uint8_t *delim);
t_file					*file_open_cache_all(struct s_allocator *allocator,
							char *path, char *mode);

#endif
