/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:30:57 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/07 11:30:59 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/clib.h"

#include <stdarg.h> // Include the header file for variadic functions
#include <string.h>

static bool result;

char *buff()
{
	static char buffer[1024];

	memset(buffer, 0x00, 1024);
	return (buffer);
}

t_bitset bitset(char *delim)
{
	return bitset_init_from_str(delim);
}

bool islowA(int32_t ch)
{
	return (ch == 'a');
}

bool islowB(int32_t ch)
{
	return (ch == 'b');
}
bool islowC(int32_t ch)
{
	return (ch == 'c');
}

void print_ok(void)
{
	printf("[%sOK%s]\n", GREEN, RESET);
	fflush(stdout);
}

void print_ko(void)
{
	printf("[%sKO%s] ", RED, RESET);
	fflush(stdout);
}

void print_test_name(char *name)
{
	printf("test : -> %s%-40s%s : ", YELLOW, name, RESET);
	fflush(stdout);
}

void put_result(bool condition)
{
	result = condition;
}

void test_setup(char *test_name)
{
	print_test_name(test_name);
}

void test_teardown(char *fn, char *name, const char *fmt, ...)
{
	if (result == false)
	{
		print_ko();

		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
		result = true;
	}
	else
		print_ok();
}

/******************************************************************************/

void test_string_length(char *case_name, char *in, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_length(in);
	put_result(expected == got);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_compare(char *case_name, char *in1, char *in2, int32_t expected)
{
	int32_t got;
	test_setup(case_name);
	got = string_compare(in1, in2);
	put_result(expected == got);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%d%s  got %s%d%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ncompare(char *case_name, char *in1, char *in2, uint64_t n, int32_t expected)
{
	int32_t got;
	test_setup(case_name);
	got = string_ncompare(in1, in2, n);
	put_result(expected == got);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%d%s  got %s%d%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_casecompare(char *case_name, char *in1, char *in2, int32_t expected)
{
	int32_t got;
	test_setup(case_name);
	got = string_casecompare(in1, in2);
	put_result(expected == got);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%d%s  got %s%d%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ncasecompare(char *case_name, char *in1, char *in2, uint64_t n, int32_t expected)
{
	int32_t got;
	test_setup(case_name);
	got = string_ncasecompare(in1, in2, n);
	put_result(expected == got);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%d%s  got %s%d%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_copy(char *case_name, char *dest, char *source, uint64_t size, char *expected)
{
	char *got;

	test_setup(case_name);
	string_copy(dest, source, size);
	got = dest;
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ccopy(char *case_name, char *dest, int32_t ch, char *source, uint64_t size, char *expected)
{
	char *got;

	test_setup(case_name);
	string_ccopy(dest, ch, source, size);
	got = dest;
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_lcopy(char *case_name, char *dest, char *source, uint64_t size, char *expected)
{
	char *got;

	test_setup(case_name);
	string_lcopy(dest, source, size);
	got = dest;
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_search_scalar(char *case_name, char *source, int32_t scalar, uint64_t n, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_search_scalar(source, scalar, n);
	put_result(string_ncompare(expected, got, n) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_search_any(char *case_name, char *source, t_bitset *bitset, uint64_t n, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_search_any(source, bitset, n);
	put_result(string_ncompare(expected, got, n) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_search_none(char *case_name, char *source, t_bitset *bitset, uint64_t n, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_search_none(source, bitset, n);
	put_result(string_ncompare(expected, got, n) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_search_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t n, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_search_predicate(source, predicate, n);
	put_result(string_ncompare(expected, got, n) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_search_sequence(char *case_name, char *source, char *needle, uint64_t n, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_search_sequence(source, needle, n);
	put_result(string_ncompare(expected, got, n) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_contains_scalar(char *case_name, char *source, int32_t scalar, uint64_t n, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_contains_scalar(source, scalar, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_contains_any(char *case_name, char *source, t_bitset *bitset, uint64_t n, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_contains_any(source, bitset, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_contains_none(char *case_name, char *source, t_bitset *bitset, uint64_t n, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_contains_none(source, bitset, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_contains_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t n, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_contains_predicate(source, predicate, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_contains_sequence(char *case_name, char *source, char *needle, uint64_t n, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_contains_sequence(source, needle, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_starts_with_scalar(char *case_name, char *source, int32_t scalar, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_starts_with_any(char *case_name, char *source, t_bitset *bitset, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_any(source, bitset);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_starts_with_none(char *case_name, char *source, t_bitset *bitset, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_none(source, bitset);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_starts_with_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_starts_with_sequence(char *case_name, char *source, char *needle, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_ends_with_scalar(char *case_name, char *source, int32_t scalar, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_ends_with_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ends_with_any(char *case_name, char *source, t_bitset *bitset, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_ends_with_any(source, bitset);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ends_with_none(char *case_name, char *source, t_bitset *bitset, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_ends_with_none(source, bitset);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ends_with_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_ends_with_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_ends_with_sequence(char *case_name, char *source, char *needle, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_ends_with_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_index_of_first_scalar(char *case_name, char *source, int32_t scalar, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_index_of_first_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_first_any(char *case_name, char *source, t_bitset *delimiters, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_index_of_first_any(source, delimiters);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_first_none(char *case_name, char *source, t_bitset *delimiters, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_index_of_first_none(source, delimiters);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_first_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_index_of_first_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_first_sequence(char *case_name, char *source, char *needle, bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_index_of_first_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}
/******************************************************************************/

void test_string_index_of_last_scalar(char *case_name, char *source, int32_t scalar, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_index_of_last_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_last_any(char *case_name, char *source, t_bitset *delimiters, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_index_of_last_any(source, delimiters);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_last_none(char *case_name, char *source, t_bitset *delimiters, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_index_of_last_none(source, delimiters);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_last_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_index_of_last_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_index_of_last_sequence(char *case_name, char *source, char *needle, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_index_of_last_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_count_scalar(char *case_name, char *source, int32_t scalar, uint64_t n, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_scalar(source, scalar, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_any(char *case_name, char *source, t_bitset *any, uint64_t n, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_any(source, any, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_none(char *case_name, char *source, t_bitset *none, uint64_t n, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_none(source, none, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t n, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_predicate(source, predicate, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_sequence(char *case_name, char *source, char *needle, uint64_t n, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_sequence(source, needle, n);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_count_until_scalar(char *case_name, char *source, int32_t scalar, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_until_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_until_any(char *case_name, char *source, t_bitset *any, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_until_any(source, any);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_until_none(char *case_name, char *source, t_bitset *none, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_until_none(source, none);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_until_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_until_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_until_sequence(char *case_name, char *source, char *needle, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_until_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_count_leading_scalar(char *case_name, char *source, int32_t scalar, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_leading_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_leading_any(char *case_name, char *source, t_bitset *any, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_leading_any(source, any);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_leading_none(char *case_name, char *source, t_bitset *none, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_leading_none(source, none);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_leading_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_leading_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_leading_sequence(char *case_name, char *source, char *needle, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_leading_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_count_trailing_scalar(char *case_name, char *source, int32_t scalar, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_trailing_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_trailing_any(char *case_name, char *source, t_bitset *any, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_trailing_any(source, any);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_trailing_none(char *case_name, char *source, t_bitset *none, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_trailing_none(source, none);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_trailing_predicate(char *case_name, char *source, bool(predicate)(int32_t ch), uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_trailing_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_count_trailing_sequence(char *case_name, char *source, char *needle, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_count_trailing_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

/******************************************************************************/

void test_string_trim_left(char *case_name, t_allocator *allocator, char *source, const uint64_t amount, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_left(allocator, source, amount);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_right(char *case_name, t_allocator *allocator, char *source, const uint64_t amount, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_right(allocator, source, amount);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_both(char *case_name, t_allocator *allocator, char *source, const uint64_t amount, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_both(allocator, source, amount);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

/******************************************************************************/

void test_string_trim_leading_scalar(char *case_name, t_allocator *allocator, char *source, int32_t scalar, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_leading_scalar(allocator, source, scalar);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_leading_any(char *case_name, t_allocator *allocator, char *source, t_bitset *delimiters, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_leading_any(allocator, source, delimiters);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_leading_none(char *case_name, t_allocator *allocator, char *source, t_bitset *delimiters, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_leading_none(allocator, source, delimiters);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_leading_predicate(char *case_name, t_allocator *allocator, char *source, bool(predicate)(int32_t ch), char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_leading_predicate(allocator, source, predicate);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_leading_sequence(char *case_name, t_allocator *allocator, char *source, char *sequence, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_leading_sequence(allocator, source, sequence);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}
/******************************************************************************/

void test_string_trim_trailing_scalar(char *case_name, t_allocator *allocator, char *source, int32_t scalar, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_trailing_scalar(allocator, source, scalar);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_trailing_any(char *case_name, t_allocator *allocator, char *source, t_bitset *delimiters, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_trailing_any(allocator, source, delimiters);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_trailing_none(char *case_name, t_allocator *allocator, char *source, t_bitset *delimiters, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_trailing_none(allocator, source, delimiters);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_trailing_predicate(char *case_name, t_allocator *allocator, char *source, bool(predicate)(int32_t ch), char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_trailing_predicate(allocator, source, predicate);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_trim_trailing_sequence(char *case_name, t_allocator *allocator, char *source, char *sequence, char *expected)
{
	char *got;
	test_setup(case_name);
	got = string_trim_trailing_sequence(allocator, source, sequence);
	put_result(string_compare(expected, got) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

/******************************************************************************/

void test_string_filter_scalar(char *case_name, t_allocator *allocator, char *source, int32_t scalar, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_filter_scalar(allocator, source, scalar);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_filter_any(char *case_name, t_allocator *allocator, char *source, t_bitset *any, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_filter_any(allocator, source, any);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_filter_none(char *case_name, t_allocator *allocator, char *source, t_bitset *none, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_filter_none(allocator, source, none);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_filter_predicate(char *case_name, t_allocator *allocator, char *source, bool(predicate)(int32_t ch), char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_filter_predicate(allocator, source, predicate);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_filter_sequence(char *case_name, t_allocator *allocator, char *source, char *sequence, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_filter_sequence(allocator, source, sequence);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

/******************************************************************************/

void test_string_wcount_scalar(char *case_name, char *source, int32_t scalar, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_wcount_scalar(source, scalar);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_wcount_any(char *case_name, char *source, t_bitset *any, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_wcount_any(source, any);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_wcount_none(char *case_name, char *source, t_bitset *none, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_wcount_none(source, none);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}


void test_string_wcount_predicate(char *case_name, char *source, bool (predicate)(int32_t ch), uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_wcount_predicate(source, predicate);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}

void test_string_wcount_sequence(char *case_name, char *source, char *needle, uint64_t expected)
{
	uint64_t got;

	test_setup(case_name);
	got = string_wcount_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%lu%s  got %s%lu%s\n", GREEN, expected, RESET, RED, got, RESET);
}


/******************************************************************************/

void test_string_replace_scalar(char *case_name, t_allocator *allocator, char *source, int32_t scalar, int32_t with, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_replace_scalar(allocator, source, scalar, with);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_replace_any(char *case_name, t_allocator *allocator, char *source, t_bitset *any, int32_t with, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_replace_any(allocator, source, any, with);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_replace_none(char *case_name, t_allocator *allocator, char *source, t_bitset *none, int32_t with, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_replace_none(allocator, source, none, with);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_replace_predicate(char *case_name, t_allocator *allocator, char *source, bool(predicate)(int32_t ch), int32_t with, char *expected)
{
	char *got;

	test_setup(case_name);
	got = string_replace_predicate(allocator, source, predicate, with);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void test_string_replace_sequence(char *case_name, t_allocator *allocator, char *source, char *needle, char *with, char *expected)
{
	char *got;

	test_setup(case_name);
	// got = string_replace_sequence(allocator, source, needle, with);
	put_result(string_compare(got, expected) == 0);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%s%s\n", GREEN, expected, RESET, RED, got, RESET);
	memdealloc(allocator, got);
}

void call_test(void)
{
	t_allocator *allocator = gpa_init(NULL);
	t_bitset     set = bitset("abc");

	// test_string_length("string_length() : 1", "", 0);
	// test_string_length("string_length() : 2", "this", 4);
	// test_string_length("string_length() : 3", "aaaabbbbccccdddd", 16);
	// test_string_compare("string_compare() : 1", "a", "a", 0);
	// test_string_compare("string_compare() : 2", "b", "a", 1);
	// test_string_compare("string_compare() : 3", "a", "b", -1);
	// test_string_compare("string_compare() : 4", "", "", 0);
	// test_string_ncompare("string_ncompare() : 1", "a", "a", 1, 0);
	// test_string_ncompare("string_ncompare() : 2", "b", "a", 1, 1);
	// test_string_ncompare("string_ncompare() : 3", "a", "b", 1, -1);
	// test_string_ncompare("string_ncompare() : 4", "", "", 1, 0);
	// test_string_casecompare("string_casecompare() : 1", "A", "a", 0);
	// test_string_casecompare("string_casecompare() : 2", "b", "A", 1);
	// test_string_casecompare("string_casecompare() : 3", "a", "B", -1);
	// test_string_casecompare("string_casecompare() : 4", "", "", 0);
	// test_string_ncasecompare("string_ncasecompare() : 4", "", "", 1, 0);
	// test_string_ncasecompare("string_ncasecompare() : 1", "A", "a", 1, 0);
	// test_string_ncasecompare("string_ncasecompare() : 2", "b", "A", 1, 1);
	// test_string_ncasecompare("string_ncasecompare() : 3", "a", "B", 1, -1);
	// test_string_ncasecompare("string_ncasecompare() : 4", "", "", 1, 0);
	// test_string_copy("string_copy() : 1", buff(), "This is a test", 15, "This is a test");
	// test_string_copy("string_copy() : 2", buff(), "This is a test of a long string", 15, "This is a test");
	// test_string_ccopy("string_ccopy() : 1", buff(), ' ', "This is a test", 1024, "This");
	// test_string_ccopy("string_ccopy() : 2", buff(), ' ', "is a test", 1024, "is");
	// test_string_ccopy("string_ccopy() : 3", buff(), ' ', "a test", 1024, "a");
	// test_string_ccopy("string_ccopy() : 4", buff(), ' ', "test", 1024, "test");
	// test_string_lcopy("string_lcopy() : 1", buff(), "This is a test", 15, "This is a test");
	// test_string_lcopy("string_lcopy() : 2", buff(), "This is a test of a long string", 15, "This is a test");
	// test_string_search_scalar("string_search_scalar() : 1", "This is a test", 'T', 13, "This is a test");
	// test_string_search_scalar("string_search_scalar() : 2", "This is a testz", 'z', 15, "z");
	// test_string_search_scalar("string_search_scalar() : 3", "This is a testz", ' ', 15, " is a testz");
	// test_string_search_scalar("string_search_scalar() : 4", "This is a testz", 'G', 15, NULL);
	// test_string_search_any("string_seach_any() : 1", "000aaabbbccc000", &set, 15, "aaabbbccc000");
	// set = bitset("bc");
	// test_string_search_any("string_seach_any() : 2", "000aaabbbccc000", &set, 15, "bbbccc000");
	// set = bitset("c");
	// test_string_search_any("string_seach_any() : 3", "000aaabbbccc000", &set, 15, "ccc000");
	// set = bitset("G");
	// test_string_search_any("string_seach_any() : 4", "000aaabbbccc000", &set, 15, NULL);
	// set = bitset("0");
	// test_string_search_none("string_seach_none() : 1", "000aaabbbccc000", &set, 15, "aaabbbccc000");
	// set = bitset("0a");
	// test_string_search_none("string_seach_none() : 2", "000aaabbbccc000", &set, 15, "bbbccc000");
	// set = bitset("0ab");
	// test_string_search_none("string_seach_none() : 3", "000aaabbbccc000", &set, 15, "ccc000");
	// set = bitset("G");
	// test_string_search_none("string_seach_none() : 4", "000aaabbbccc000", &set, 15, "000aaabbbccc000");
	// test_string_search_predicate("string_search_predicate() : 1", "000aaabbbccc000", islowA, 15, "aaabbbccc000");
	// test_string_search_predicate("string_search_predicate() : 2", "000aaabbbccc000", islowB, 15, "bbbccc000");
	// test_string_search_predicate("string_search_predicate() : 3", "000aaabbbccc000", islowC, 15, "ccc000");
	// test_string_search_sequence("string_search_sequence() : 1", "aaabbbcccddd", "aaa", 12, "aaabbbcccddd");
	// test_string_search_sequence("string_search_sequence() : 2", "aaabbbcccddd", "bbb", 12, "bbbcccddd");
	// test_string_search_sequence("string_search_sequence() : 3", "aaabbbcccddd", "ccc", 12, "cccddd");
	// test_string_search_sequence("string_search_sequence() : 4", "aaabbbcccddd", "ddd", 12, "ddd");
	// test_string_search_sequence("string_search_sequence() : 5", "aaabbbcccddd", "GGG", 12, NULL);
	// test_string_contains_scalar("string_contains_scalar() : 1", "abcdefhijklmnopqrstuvwxyz", 'a', 26, true);
	// test_string_contains_scalar("string_contains_scalar() : 2", "abcdefhijklmnopqrstuvwxyz", 'z', 26, true);
	// test_string_contains_scalar("string_contains_scalar() : 3", "abcdefhijklmnopqrstuvwxyz", 'A', 26, false);
	// test_string_contains_scalar("string_contains_scalar() : 4", "abcdefhijklmnopqrstuvwxyz", 'Z', 26, false);
	// test_string_contains_scalar("string_contains_scalar() : 5", "abcdefhijklmno0pqrstuvwxyz", '0', 26, true);
	// set = bitset("hjkl");
	// test_string_contains_any("string_contains_any() : 1", "abcdefhijklmnopqrstuvwxyz", &set, 26, true);
	// set = bitset("BhjklA");
	// test_string_contains_any("string_contains_any() : 2", "abcdefhijklmnopqrstuvwxyz", &set, 26, true);
	// set = bitset("ABCDEF");
	// test_string_contains_any("string_contains_any() : 3", "abcdefhijklmnopqrstuvwxyz", &set, 26, false);
	// set = bitset("HJLK");
	// test_string_contains_none("string_contains_none() : 1", "abcdefHIJKLmnopqrstuvwxyz", &set, 26, false);
	// set = bitset("BhjklA");
	// test_string_contains_none("string_contains_none() : 2", "abcdefHIJKLmnopqrstuvwxyz", &set, 26, true);
	// set = bitset("a");
	// test_string_contains_none("string_contains_none() : 3", "abcdefHIJKLmnopqrstuvwxyz", &set, 26, false);
	// test_string_contains_predicate("string_contains_predicate() : 1", "abcdefHIJKLmnopqrstuvwxyz", is_upper, 26, true);
	// test_string_contains_predicate("string_contains_predicate() : 2", "ABCDEFhijklMNOPQRSTUVWXYZ", is_lower, 26, true);
	// test_string_contains_predicate("string_contains_predicate() : 3", "ABCDEFhijklMNOPQRSTUVWXYZ", is_spaces, 26, false);
	// test_string_contains_sequence("string_contains_sequence() : 1", "abcdefhijklmnopqrstuvwxyz", "z", 26, true);
	// test_string_contains_sequence("string_contains_sequence() : 2", "abcdefhijklmnopqrstuvwxyz", "a", 26, true);
	// test_string_contains_sequence("string_contains_sequence() : 3", "abcdefhijklmnopqrstuvwxyz", "abcdefhijklmnopqrstuvwxyz", 26, true);

	// test_string_starts_with_scalar("string_starts_with_scalar() : 1", "abcdef", 'a', true);
	// test_string_starts_with_scalar("string_starts_with_scalar() : 2", "abcdef", 'b', false);
	// test_string_starts_with_scalar("string_starts_with_scalar() : 3", "abcdef", '7', false);

	// set = bitset("abc");
	// test_string_starts_with_any("string_starts_with_any() : 1", "abcdef", &set, true);
	// test_string_starts_with_any("string_starts_with_any() : 2", "bbcdef", &set, true);
	// test_string_starts_with_any("string_starts_with_any() : 3", "cbcdef", &set, true);
	// test_string_starts_with_any("string_starts_with_any() : 4", "Zbcdef", &set, false);
	// test_string_starts_with_any("string_starts_with_any() : 5", "Ibcdef", &set, false);
	// test_string_starts_with_any("string_starts_with_any() : 6", "Gbcdef", &set, false);

	// set = bitset("ABC");
	// test_string_starts_with_none("string_starts_with_none() : 1", "abcdef", &set, true);
	// test_string_starts_with_none("string_starts_with_none() : 2", "bbcdef", &set, true);
	// test_string_starts_with_none("string_starts_with_none() : 3", "cbcdef", &set, true);
	// test_string_starts_with_none("string_starts_with_none() : 4", "Abcdef", &set, false);
	// test_string_starts_with_none("string_starts_with_none() : 5", "Bbcdef", &set, false);
	// test_string_starts_with_none("string_starts_with_none() : 6", "Cbcdef", &set, false);

	// test_string_starts_with_predicate("string_starts_with_predicate : 1", "abcdef", is_alpha, true);
	// test_string_starts_with_predicate("string_starts_with_predicate : 2", "abcdef", is_digit, false);

	// test_string_starts_with_sequence("string_starts_with_sequence() : 1", "aaabbbcccddd", "aaa", true);
	// test_string_starts_with_sequence("string_starts_with_sequence() : 2", "aaabbbcccddd", "aa", true);
	// test_string_starts_with_sequence("string_starts_with_sequence() : 3", "aaabbbcccddd", "a", true);
	// test_string_starts_with_sequence("string_starts_with_sequence() : 4", "aaabbbcccddd", "b", false);
	// test_string_starts_with_sequence("string_starts_with_sequence() : 5", "aaabbbcccddd", "aaabbbcccddd", true);

	// test_string_ends_with_scalar("string_ends_with_scalar() : 1", "abcdef", 'f', true);
	// test_string_ends_with_scalar("string_ends_with_scalar() : 2", "abcdef", 'e', false);
	// test_string_ends_with_scalar("string_ends_with_scalar() : 3", "abcdef", 'a', false);

	// set = bitset("def");
	// test_string_ends_with_any("string_ends_with_any() : 1", "abcdef", &set, true);
	// test_string_ends_with_any("string_ends_with_any() : 2", "bbcdee", &set, true);
	// test_string_ends_with_any("string_ends_with_any() : 3", "cbcded", &set, true);
	// test_string_ends_with_any("string_ends_with_any() : 4", "ZbcdeZ", &set, false);
	// test_string_ends_with_any("string_ends_with_any() : 5", "IbcdeI", &set, false);
	// test_string_ends_with_any("string_ends_with_any() : 6", "GbcdeG", &set, false);

	// set = bitset("ABC");
	// test_string_ends_with_none("string_ends_with_none() : 1", "abcdef", &set, true);
	// test_string_ends_with_none("string_ends_with_none() : 2", "bbcdef", &set, true);
	// test_string_ends_with_none("string_ends_with_none() : 3", "cbcdef", &set, true);
	// test_string_ends_with_none("string_ends_with_none() : 4", "AbcdeA", &set, false);
	// test_string_ends_with_none("string_ends_with_none() : 5", "BbcdeB", &set, false);
	// test_string_ends_with_none("string_ends_with_none() : 6", "CbcdeC", &set, false);

	// test_string_ends_with_predicate("string_ends_with_predicate : 1", "00000f", is_alpha, true);
	// test_string_ends_with_predicate("string_ends_with_predicate : 2", "00000f", is_digit, false);
	// test_string_ends_with_predicate("string_ends_with_predicate : 3", "f", is_alpha, true);
	// test_string_ends_with_predicate("string_ends_with_predicate : 4", "f", is_digit, false);

	// test_string_ends_with_sequence("string_ends_with_sequence() : 1", "aaabbbcccddd", "ddd", true);
	// test_string_ends_with_sequence("string_ends_with_sequence() : 2", "aaabbbcccddd", "dd", true);
	// test_string_ends_with_sequence("string_ends_with_sequence() : 3", "aaabbbcccddd", "d", true);
	// test_string_ends_with_sequence("string_ends_with_sequence() : 4", "aaabbbcccddd", "b", false);
	// test_string_ends_with_sequence("string_ends_with_sequence() : 5", "aaabbbcccddd", "aaabbbcccddd", true);

	// test_string_index_of_first_scalar("string_index_of_first_scalar() : 1", "a", 'a', 0);
	// test_string_index_of_first_scalar("string_index_of_first_scalar() : 2", "abc", 'c', 2);
	// test_string_index_of_first_scalar("string_index_of_first_scalar() : 3", "abc", 'b', 1);

	// set = bitset("abcd");
	// test_string_index_of_first_any("string_index_of_first_any() : 1", "aaa bbb ccc ddd", &set, 0);
	// set = bitset("bcd");
	// test_string_index_of_first_any("string_index_of_first_any() : 2", "aaa bbb ccc ddd", &set, 4);
	// set = bitset("cd");
	// test_string_index_of_first_any("string_index_of_first_any() : 3", "aaa bbb ccc ddd", &set, 8);
	// set = bitset("d");
	// test_string_index_of_first_any("string_index_of_first_any() : 4", "aaa bbb ccc ddd", &set, 12);

	// set = bitset(" ");
	// test_string_index_of_first_none("string_index_of_first_none() : 1", "aaa bbb ccc ddd", &set, 0);
	// set = bitset(" a");
	// test_string_index_of_first_none("string_index_of_first_none() : 2", "aaa bbb ccc ddd", &set, 4);
	// set = bitset("a b");
	// test_string_index_of_first_none("string_index_of_first_none() : 3", "aaa bbb ccc ddd", &set, 8);
	// set = bitset("abc ");
	// test_string_index_of_first_none("string_index_of_first_none() : 4", "aaa bbb ccc ddd", &set, 12);

	// test_string_index_of_first_predicate("string_index_of_first_predicate() : 1", "000111aaa   ABC", is_digit, 0);
	// test_string_index_of_first_predicate("string_index_of_first_predicate() : 2", "000111aaa   ABC", is_alpha, 6);
	// test_string_index_of_first_predicate("string_index_of_first_predicate() : 3", "000111aaa   ABC", is_spaces, 9);
	// test_string_index_of_first_predicate("string_index_of_first_predicate() : 4", "000111aaa   ABC", is_upper, 12);
	// test_string_index_of_first_predicate("string_index_of_first_predicate() : 5", "000111aaa   ", is_newline, NOTFOUND);

	// test_string_index_of_first_sequence("string_index_of_first_sequence() : 1","aaabbbcccddd", "aaa", 0);
	// test_string_index_of_first_sequence("string_index_of_first_sequence() : 2","aaabbbcccddd", "bbb", 3);
	// test_string_index_of_first_sequence("string_index_of_first_sequence() : 3","aaabbbcccddd", "ccc", 6);
	// test_string_index_of_first_sequence("string_index_of_first_sequence() : 4","aaabbbcccddd", "ddd", 9);
	// test_string_index_of_first_sequence("string_index_of_first_sequence() : 5","aaabbbcccddd", "eee", NOTFOUND);

	// test_string_index_of_last_scalar("string_index_of_last_scalar() : 1", "abcdef", 'a', 0);
	// test_string_index_of_last_scalar("string_index_of_last_scalar() : 2", "abcdef", 'c', 2);
	// test_string_index_of_last_scalar("string_index_of_last_scalar() : 3", "abcdef", 'f', 5);
	// test_string_index_of_last_scalar("string_index_of_last_scalar() : 4", "abcdef", 'z', NOTFOUND);

	// set = bitset("abc ");
	// test_string_index_of_last_any("string_index_of_last_any() : 1", "aaa bbb ccc", &set, 10);
	// set = bitset(" ");
	// test_string_index_of_last_any("string_index_of_last_any() : 2", "aaa bbb ccc", &set, 7);
	// set = bitset("b");
	// test_string_index_of_last_any("string_index_of_last_any() : 3", "aaa bbb ccc", &set, 6);

	// set = bitset("ab ");
	// test_string_index_of_last_none("string_index_of_last_none() : 1", "aaa bbb ccc", &set, 10);
	// set = bitset("abc");
	// test_string_index_of_last_none("string_index_of_last_none() : 2", "aaa bbb ccc", &set, 7);
	// set = bitset("ac ");
	// test_string_index_of_last_none("string_index_of_last_none() : 3", "aaa bbb ccc", &set, 6);
	// set = bitset("ac b");
	// test_string_index_of_last_none("string_index_of_last_none() : 4", "aaa bbb ccc", &set, 0);

	// test_string_index_of_last_predicate("string_index_of_last_predicate() : 1", "aaa   CCC000", is_lower, 2);
	// test_string_index_of_last_predicate("string_index_of_last_predicate() : 2", "aaa   CCC000", is_spaces, 5);
	// test_string_index_of_last_predicate("string_index_of_last_predicate() : 3", "aaa   CCC000", is_upper, 8);
	// test_string_index_of_last_predicate("string_index_of_last_predicate() : 4", "aaa   CCC000", is_digit, 11);
	// test_string_index_of_last_predicate("string_index_of_last_predicate() : 4", "aaa   CCC000", is_newline, NOTFOUND);

	// test_string_index_of_last_sequence("string_index_of_last_sequence() : 1", "aaabbbcccddd", "ddd", 9);
	// test_string_index_of_last_sequence("string_index_of_last_sequence() : 2", "aaabbbcccddd", "ccc", 6);
	// test_string_index_of_last_sequence("string_index_of_last_sequence() : 3", "aaabbbcccddd", "bbb", 3);
	// test_string_index_of_last_sequence("string_index_of_last_sequence() : 4", "aaabbbcccddd", "aaa", 0);
	// test_string_index_of_last_sequence("string_index_of_last_sequence() : 5", "aaabbbcccddd", "zzz", NOTFOUND);

	// test_string_count_scalar("string_count_scalar() : 1", "aaabbbccc", 'a', 9, 3);
	// test_string_count_scalar("string_count_scalar() : 2", "aaabbbccc", 'b', 3, 0);
	// test_string_count_scalar("string_count_scalar() : 2", "aaabbbccc", 'b', 9, 3);
	// test_string_count_scalar("string_count_scalar() : 3", "aaabbbccc", 'c', 9, 3);
	// test_string_count_scalar("string_count_scalar() : 4", "aaabbbccc", ' ', 9, 0);

	// set = bitset("abc");
	// test_string_count_any("string_count_any() : 1", "aaabbbccc", &set, 9, 9);
	// set = bitset("ab");
	// test_string_count_any("string_count_any() : 2", "aaabbbccc", &set, 9, 6);
	// set = bitset("a");
	// test_string_count_any("string_count_any() : 3", "aaabbbccc", &set, 3, 3);
	// set = bitset("a");
	// test_string_count_any("string_count_any() : 4", "aaabbbccc", &set, 9, 3);
	// set = bitset(" ");
	// test_string_count_any("string_count_any() : 5", "aaabbbccc", &set, 9, 0);

	// set = bitset("abc");
	// test_string_count_none("string_count_none() : 1", "aaabbbccc", &set, 9, 0);
	// set = bitset("ab");
	// test_string_count_none("string_count_none() : 2", "aaabbbccc", &set, 9, 3);
	// set = bitset("a");
	// test_string_count_none("string_count_none() : 3", "aaabbbccc", &set, 3, 0);
	// set = bitset("a");
	// test_string_count_none("string_count_none() : 4", "aaabbbccc", &set, 9, 6);
	// set = bitset(" ");
	// test_string_count_none("string_count_none() : 5", "aaabbbccc", &set, 9, 9);

	// test_string_count_predicate("string_count_predicate() : 1", "aaaBBB### 000", is_lower, 15, 3);
	// test_string_count_predicate("string_count_predicate() : 2", "aaaBBB### 000", is_upper, 15, 3);
	// test_string_count_predicate("string_count_predicate() : 3", "aaaBBB### 000", is_punct, 15, 6);
	// test_string_count_predicate("string_count_predicate() : 4", "aaaBBB### 000", is_spaces, 15, 3);
	// test_string_count_predicate("string_count_predicate() : 5", "aaaBBB### 000", is_digit, 15, 3);
	// test_string_count_predicate("string_count_predicate() : 6", "aaaBBB### 000", is_control, 15, 0);

	// test_string_count_sequence("string_count_sequence() : 1", "aaabbbaaabbbaaabbb", "aaa", 18, 3);
	// test_string_count_sequence("string_count_sequence() : 2", "aaabbbaaabbbaaabbb", "bbb", 18, 3);
	// test_string_count_sequence("string_count_sequence() : 3", "aaabbbaaabbbaaabbb", "zzz", 18, 0);

	// test_string_count_until_scalar("string_count_until_scalar() : 1", "aaabbbcccddd", 'b', 3);
	// test_string_count_until_scalar("string_count_until_scalar() : 2", "aaabbbcccddd", 'c', 6);
	// test_string_count_until_scalar("string_count_until_scalar() : 3", "aaabbbcccddd", 'd', 9);
	// test_string_count_until_scalar("string_count_until_scalar() : 4", "aaabbbcccddd", 'z', 12);

	// set = bitset(" ");
	// test_string_count_until_any("string_count_until_any() : 1", "aaa bbb ccc ddd", &set, 3);
	// test_string_count_until_any("string_count_until_any() : 2", "aaabbb ccc ddd", &set, 6);
	// test_string_count_until_any("string_count_until_any() : 3", "aaabbbccc ddd", &set, 9);
	// test_string_count_until_any("string_count_until_any() : 4", "aaabbbcccddd", &set, 12);

	// test_string_count_until_none("string_count_until_none() : 1", "aaa bbb ccc ddd", &set, 0);
	// test_string_count_until_none("string_count_until_none() : 2", "    bbb ccc ddd", &set, 4);
	// test_string_count_until_none("string_count_until_none() : 2", " ccc ddd", &set, 8);
	// test_string_count_until_none("string_count_until_none() : 2", " ddd", &set, 12);
	// test_string_count_until_none("string_count_until_none() : 2", " ", &set, 15);

	// test_string_count_until_predicate("string_count_until_predicate() : 1", "aaa bbb ccc ddd", is_spaces, 3);
	// test_string_count_until_predicate("string_count_until_predicate() : 2", "aaabbb ccc ddd", is_spaces, 6);
	// test_string_count_until_predicate("string_count_until_predicate() : 3", "aaabbbccc ddd", is_spaces, 9);
	// test_string_count_until_predicate("string_count_until_predicate() : 4", "aaabbbcccddd", is_spaces, 12);

	// test_string_count_until_sequence("string_count_until_sequence() : 1", "aaa bbb ccc ddd", "ddd", 12);
	// test_string_count_until_sequence("string_count_until_sequence() : 1", "aaa bbb ccc ddd", "ccc", 8);
	// test_string_count_until_sequence("string_count_until_sequence() : 1", "aaa bbb ccc ddd", "bbb", 4);
	// test_string_count_until_sequence("string_count_until_sequence() : 1", "aaa bbb ccc ddd", "aaa", 0);

	// test_string_count_leading_scalar("string_count_leading_scalar() : 1", "aaabbbcccddd", 'a', 3);
	// test_string_count_leading_scalar("string_count_leading_scalar() : 2", "bbbcccddd", 'b', 3);
	// test_string_count_leading_scalar("string_count_leading_scalar() : 3", "cccddd", 'c', 3);
	// test_string_count_leading_scalar("string_count_leading_scalar() : 4", "ddd", 'd', 3);
	// test_string_count_leading_scalar("string_count_leading_scalar() : 5", "", 'z', 0);
	// test_string_count_leading_scalar("string_count_leading_scalar() : 6", "aaabbbccc", 'z', 0);

	// set = bitset("a");
	// test_string_count_leading_any("string_count_leading_any() : 1", "aaabbbcccddd", &set, 3);
	// set = bitset("ab");
	// test_string_count_leading_any("string_count_leading_any() : 2", "aaabbbcccddd", &set, 6);
	// set = bitset("abc");
	// test_string_count_leading_any("string_count_leading_any() : 3", "a Locale: en_US.UTF-8aabbbcccddd", &set, 9);
	// set = bitset("abcd");
	// test_string_count_leading_any("string_count_leading_any() : 4", "aaabbbcccddd", &set, 12);
	// set = bitset("abcd");
	// test_string_count_leading_any("string_count_leading_any() : 5", "aaabbbcccddd", &set, 12);

	// set = bitset("bcd");
	// test_string_count_leading_none("string_count_leading_none() : 1", "aaabbbcccddd", &set, 3);
	// set = bitset("cd");
	// test_string_count_leading_none("string_count_leading_none() : 2", "aaabbbcccddd", &set, 6);
	// set = bitset("d");
	// test_string_count_leading_none("string_count_leading_none() : 3", "aaabbbcccddd", &set, 9);
	// set = bitset(" ");
	// test_string_count_leading_none("string_count_leading_none() : 4", "aaabbbcccddd", &set, 12);

	// test_string_count_leading_predicate("string_count_leading_predicate() : 1", "aaabbbcccddd", is_alpha, 12);
	// test_string_count_leading_predicate("string_count_leading_predicate() : 2", "AAABBBCCCDDD", is_lower, 0);
	// test_string_count_leading_predicate("string_count_leading_predicate() : 3", "0aaaaaaaaaaa", is_digit, 1);

	// test_string_count_leading_sequence("string_count_leading_sequence() : 1", "ababab_aaaa_ababab", "ab", 3);
	// test_string_count_leading_sequence("string_count_leading_sequence() : 2", "ababab", "ab", 3);
	// test_string_count_leading_sequence("string_count_leading_sequence() : 3", "", "a", 0);
	// test_string_count_leading_sequence("string_count_leading_sequence() : 4", "aaaabbbccd", "aaaa", 1);

	// test_string_count_trailing_scalar("string_count_trailing_scalar() : 1", "aaabbbcccddd", 'd',3 );
	// test_string_count_trailing_scalar("string_count_trailing_scalar() : 2", "aaabbbccc", 'c',3 );
	// test_string_count_trailing_scalar("string_count_trailing_scalar() : 3", "aaabbb", 'b',3 );
	// test_string_count_trailing_scalar("string_count_trailing_scalar() : 4", "aaa", 'a',3 );
	// test_string_count_trailing_scalar("string_count_trailing_scalar() : 5", "aaabbbcccddd", 'z',0 );

	// set = bitset(" \t_");
	// test_string_count_trailing_any("string_count_trailing_any() : 1", "hello _	", &set, 5);
	// set = bitset(" ");
	// test_string_count_trailing_any("string_count_trailing_any() : 2", "hello ", &set, 2);
	// set = bitset("abc");
	// test_string_count_trailing_any("string_count_trailing_any() : 3", "helloabcabcabcbababcbabcabc", &set, 22);

	// set = bitset("hello");
	// test_string_count_trailing_none("string_count_trailing_none() : 1", "hello _	", &set, 5);
	// set = bitset("hello");
	// test_string_count_trailing_none("string_count_trailing_none() : 2", "hello ", &set, 2);
	// set = bitset("hello");            Locale: en_US.UTF-8
	// test_string_count_trailing_none("string_count_trailing_none() : 3", "helloabcabcabcbababcbabcabc", &set, 22);

	// test_string_count_trailing_predicate("string_count_trailing_predicate() : 1", "0aaaaa55555%%%%%", is_punct, 5);
	// test_string_count_trailing_predicate("string_count_trailing_predicate() : 2", "0aaaaa55555", is_digit, 5);
	// test_string_count_trailing_predicate("string_count_trailing_predicate() : 3", "0aaaaa", is_lower, 5);
	// test_string_count_trailing_predicate("string_count_trailing_predicate() : 3", "0", is_digit, 1);
	// test_string_count_trailing_predicate("string_count_trailing_predicate() : 6", "0aaaaa55555%%%%%", is_control, 0);

	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 1", "aaabbbcccddd", "ddd", 1);
	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 2", "aaabbbccc", "ccc", 1);
	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 3", "aaabbb", "bbb", 1);
	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 4", "aaa", "aaa", 1);
	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 5", "aaa", "aa", 1);
	// test_string_count_trailing_sequence("string_count_trailing_sequence() : 6", "aaa", "zzzzzzz", 0);

	// test_string_trim_left("string_trim_left() : 1", allocator, "     hello world", 5, "hello world");
	// test_string_trim_left("string_trim_left() : 2", allocator, "    hello world", 4, "hello world");
	// test_string_trim_left("string_trim_left() : 3", allocator, "   hello world", 3, "hello world");
	// test_string_trim_left("string_trim_left() : 4", allocator, "  hello world", 2, "hello world");
	// test_string_trim_left("string_trim_left() : 5", allocator, " hello world", 1, "hello world");
	// test_string_trim_left("string_trim_left() : 6", allocator, "hello world", 0, "hello world");
	// test_string_trim_left("string_trim_left() : 7", allocator, "hello world", 11, "");
	// test_string_trim_left("string_trim_left() : 8", allocator, "hello world", 31, "");

	// test_string_trim_right("string_trim_right() : 1", allocator, "hello world ", 5, "hello world");
	// test_string_trim_right("string_trim_right() : 2", allocator, "hello world ", 4, "hello world");
	// test_string_trim_right("string_trim_right() : 3", allocator, "hello world ", 3, "hello world");
	// test_string_trim_right("string_trim_right() : 4", allocator, "hello world ", 2, "hello world");
	// test_string_trim_right("string_trim_right() : 5", allocator, "hello world ", 1, "hello world");
	// test_string_trim_right("string_trim_right() : 6", allocator, "hello world", 0, "hello world");
	// test_string_trim_right("string_trim_right() : 7", allocator, "hello world", 11, "");
	// test_string_trim_right("string_trim_right() : 8", allocator, "hello world", 31, "");

	// test_string_trim_both("string_trim_both() : 1", allocator, "     hello world ", 5, "hello world");
	// test_string_trim_both("string_trim_both() : 2", allocator, "    hello world ", 4, "hello world");
	// test_string_trim_both("string_trim_both() : 3", allocator, "   hello world ", 3, "hello world");
	// test_string_trim_both("string_trim_both() : 4", allocator, "  hello world ", 2, "hello world");
	// test_string_trim_both("string_trim_both() : 5", allocator, " hello world ", 1, "hello world");
	// test_string_trim_both("string_trim_both() : 6", allocator, "hello world", 0, "hello world");
	// test_string_trim_both("string_trim_both() : 7", allocator, "hello world", 11, "");
	// test_string_trim_both("string_trim_both() : 8", allocator, "hello world", 31, "");

	// test_string_trim_leading_scalar("string_trim_leading_scalar() : 1", allocator, "aaabbbccc", 'a', "bbbccc");
	// test_string_trim_leading_scalar("string_trim_leading_scalar() : 2", allocator, "aabbbccc", 'a', "bbbccc");
	// test_string_trim_leading_scalar("string_trim_leading_scalar() : 3", allocator, "abbbccc", 'a', "bbbccc");
	// test_string_trim_leading_scalar("string_trim_leading_scalar() : 4", allocator, "bbbccc", 'a', "bbbccc");
	// test_string_trim_leading_scalar("string_trim_leading_scalar() : 5", allocator, "bbbccczzz", 'z', "bbbccczzz");

	// set = bitset("a");
	// test_string_trim_leading_any("string_trim_leading_any() : 1", allocator, "aaaabbbccd", &set, "bbbccd");
	// set = bitset("ab");
	// test_string_trim_leading_any("string_trim_leading_any() : 2", allocator, "aaaabbbccd", &set, "ccd");
	// set = bitset("abc");
	// test_string_trim_leading_any("string_trim_leading_any() : 3", allocator, "aaaabbbccd", &set, "d");
	// set = bitset("abcd");
	// test_string_trim_leading_any("string_trim_leading_any() : 4", allocator, "aaaabbbccd", &set, "");

	// set = bitset("bcd");
	// test_string_trim_leading_none("string_trim_leading_none() : 1", allocator, "aaaabbbccd", &set, "bbbccd");
	// set = bitset("cd");
	// test_string_trim_leading_none("string_trim_leading_none() : 2", allocator, "aaaabbbccd", &set, "ccd");
	// set = bitset("d");
	// test_string_trim_leading_none("string_trim_leading_none() : 3", allocator, "aaaabbbccd", &set, "d");
	// set = bitset("abcd");
	// test_string_trim_leading_none("string_trim_leading_none() : 4", allocator, "aaaabbbccd", &set, "aaaabbbccd");

	// test_string_trim_leading_predicate("string_trim_leading_predicate() : 1", allocator, "aaaa111$$B", is_lower, "111$$B");
	// test_string_trim_leading_predicate("string_trim_leading_predicate() : 2", allocator, "111$$B", is_digit, "$$B");
	// test_string_trim_leading_predicate("string_trim_leading_predicate() : 3", allocator, "$$B", is_punct, "B");
	// test_string_trim_leading_predicate("string_trim_leading_predicate() : 4", allocator, "B", is_upper, "");

	// test_string_trim_leading_sequence("string_trim_leading_sequence() : 1", allocator, "aaaabbbccd", "aaaa", "bbbccd");
	// test_string_trim_leading_sequence("string_trim_leading_sequence() : 1", allocator, "bbbccd", "bbb", "ccd");
	// test_string_trim_leading_sequence("string_trim_leading_sequence() : 1", allocator, "ccd", "cc", "d");

	// test_string_trim_trailing_scalar("string_trim_trailing_scalar() : 1", allocator, "dccbbbaaaa", 'a', "dccbbb");
	// test_string_trim_trailing_scalar("string_trim_trailing_scalar() : 2", allocator, "dccbbb", 'b', "dcc");
	// test_string_trim_trailing_scalar("string_trim_trailing_scalar() : 3", allocator, "dcc", 'c', "d");
	// test_string_trim_trailing_scalar("string_trim_trailing_scalar() : 4", allocator, "d", 'd', "");

	// set = bitset(" ");
	// test_string_trim_trailing_any("string_trim_trailing_any() : 1", allocator, "Hello World  ", &set, "Hello World");
	// test_string_trim_trailing_any("string_trim_trailing_any() : 2", allocator, "Hello World ", &set, "Hello World");
	// test_string_trim_trailing_any("string_trim_trailing_any() : 3", allocator, "Hello World", &set, "Hello World");

	// set = bitset("HelloWorld");
	// test_string_trim_trailing_none("string_trim_trailing_none() : 1", allocator, "Hello World  ", &set, "Hello World");
	// test_string_trim_trailing_none("string_trim_trailing_none() : 2", allocator, "Hello World ", &set, "Hello World");
	// test_string_trim_trailing_none("string_trim_trailing_none() : 3", allocator, "Hello World", &set, "Hello World");

	// test_string_trim_trailing_predicate("string_trim_trailing_predicate() : 1", allocator, "Hello World  ", is_spaces, "Hello World");
	// test_string_trim_trailing_predicate("string_trim_trailing_predicate() : 2", allocator, "Hello World0123456789", is_digit, "Hello World");
	// test_string_trim_trailing_predicate("string_trim_trailing_predicate() : 3", allocator, "Hello WorldHHHHH", is_upper, "Hello World");

	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 1", allocator, "abbcccddddeeeee", "eeeee", "abbcccdddd");
	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 2", allocator, "abbcccdddd", "dddd", "abbccc");
	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 3", allocator, "abbccc", "ccc", "abb");
	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 4", allocator, "abb", "bb", "a");
	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 5", allocator, "a", "z", "a");
	// test_string_trim_trailing_sequence("string_trim_trailing_sequence() : 6", allocator, "a", "a", "");

	// test_string_filter_scalar("string_filter_scalar() : 1", allocator, "This is a test of filtering", 'i', "Ths s a test of flterng");
	// test_string_filter_scalar("string_filter_scalar() : 2", allocator, "This is a test of filtering", 't', "This is a es of filering");
	// test_string_filter_scalar("string_filter_scalar() : 3", allocator, "This is a test of filtering", ' ', "Thisisatestoffiltering");
	// test_string_filter_scalar("string_filter_scalar() : 4", allocator, "This is a test of filtering", 'z', "This is a test of filtering");

	// set = bitset("iaeouy");
	// test_string_filter_any("string_filter_any() : 1", allocator, "This is a test of filtering", &set, "Ths s  tst f fltrng");
	// set = bitset("This is a test of filtering");
	// test_string_filter_any("string_filter_any() : 2", allocator, "This is a test of filtering", &set, "");
	// set = bitset("a ");
	// test_string_filter_any("string_filter_any() : 3", allocator, "This is a test of filtering", &set, "Thisistestoffiltering");

	// set = bitset("iaeouy");
	// test_string_filter_none("string_filter_none() : 1", allocator, "This is a test of filtering", &set, "iiaeoiei");
	// set = bitset("This is a test of filtering");
	// test_string_filter_none("string_filter_none() : 2", allocator, "This is a test of filtering", &set, "This is a test of filtering");
	// set = bitset("a ");
	// test_string_filter_none("string_filter_none() : 3", allocator, "This is a test of filtering", &set, "  a   ");

	// test_string_filter_predicate("string_filter_predicate() : 1", allocator, "This ;043is **a test \t\vof QQQQfiltering", is_digit, "This ;is **a test \t\vof QQQQfiltering");
	// test_string_filter_predicate("string_filter_predicate() : 1", allocator, "This ;is **a test \t\vof QQQQfiltering", is_punct, "This is a test \t\vof QQQQfiltering");
	// test_string_filter_predicate("string_filter_predicate() : 1", allocator, "This is a test \t\vof QQQQfiltering", is_control, "This is a test of QQQQfiltering");
	// test_string_filter_predicate("string_filter_predicate() : 1", allocator, "This is a test of QQQQfiltering", is_upper, "his is a test of filtering");

	// test_string_filter_sequence("string_filter_sequence() : 1", allocator, "www.google.com", "www.", "google.com");
	// test_string_filter_sequence("string_filter_sequence() : 2", allocator, "https://www.google.com", "https://www.", "google.com");
	// test_string_filter_sequence("string_filter_sequence() : 3", allocator, "https://www.google.com", "", "https://www.google.com");
	// test_string_filter_sequence("string_filter_sequence() : 4", allocator, "abTabhabiabsab abiabsab abaab abtabeabsabtab", "ab", "This is a test");

	test_string_wcount_scalar("string_wcount_scalar() : 1", "This is a lovely string", ' ', 5);
	test_string_wcount_scalar("string_wcount_scalar() : 2", "@This@@ @@is@@ @@a@@ @@lovely@@ @@string@", '@', 9);
	test_string_wcount_scalar("string_wcount_scalar() : 3", "This", ' ', 1);
	test_string_wcount_scalar("string_wcount_scalar() : 4", " This ", ' ', 1);
	test_string_wcount_scalar("string_wcount_scalar() : 5", "    This     ", ' ', 1);
	test_string_wcount_scalar("string_wcount_scalar() : 6", "    Th is     ", ' ', 2);
	test_string_wcount_scalar("string_wcount_scalar() : 7", NULL, ' ', 0);

	set = bitset(" ,");
	test_string_wcount_any("string_wcount_any() : 1", "This is a test" ,&set, 4);
	test_string_wcount_any("string_wcount_any() : 2", ",This, ,is, ,a, ,test," ,&set, 4);
	set = bitset("z");
	test_string_wcount_any("string_wcount_any() : 3", ",This, ,is, ,a, ,test," ,&set, 1);
	test_string_wcount_any("string_wcount_any() : 4", ",This, ,is, ,a, ,test,zzz" ,&set, 1);

	set = bitset("Thisisatest");
	test_string_wcount_none("string_wcount_none() : 1", "This is a test" ,&set, 4);
	test_string_wcount_none("string_wcount_none() : 2", "This is a test" ,&set, 4);
	test_string_wcount_none("string_wcount_none() : 3", "" ,&set, 0);

	test_string_wcount_predicate("string_wcount_predicate() : 1", "This is a \ttest\n", is_spaces, 4);
	test_string_wcount_predicate("string_wcount_predicate() : 2", "&^This() ;is *a \ttest\n", is_punct, 4);

	test_string_wcount_sequence("string_wcount_sequence() : 1", "__This__is__a__test__", "__", 4);
	test_string_wcount_sequence("string_wcount_sequence() : 2", "__This__is__a__test__", "_", 4);
	test_string_wcount_sequence("string_wcount_sequence() : 3", "thisThisthisisthisathistestthis", "this", 4);

	// test_string_replace_scalar("string_replace_scalar() : 1", allocator, "ThGs Gs a test of a strGng", 'G', 'i', "This is a test of a string");
	// test_string_replace_scalar("string_replace_scalar() : 2", allocator, "ThGs Gs a test of a strGng", 'z', 'i', "ThGs Gs a test of a strGng");
	// test_string_replace_scalar("string_replace_scalar() : 3", allocator, "z", 'z', 'i', "i");

	// set = bitset("a");
	// test_string_replace_any("string_replace_any() : 1", allocator, "abcabcabcabc", &set, 'Z', "ZbcZbcZbcZbc");
	// set = bitset("ab");
	// test_string_replace_any("string_replace_any() : 2", allocator, "abcabcabcabc", &set, 'Z', "ZZcZZcZZcZZc");
	// set = bitset("abG");
	// test_string_replace_any("string_replace_any() : 2", allocator, "abcabcabcabc", &set, 'Z', "ZZcZZcZZcZZc");
	// set = bitset("abc");
	// test_string_replace_any("string_replace_any() : 3", allocator, "abcabcabcabc", &set, 'Z', "ZZZZZZZZZZZZ");

	// set = bitset("a");
	// test_string_replace_none("string_replace_none() : 1", allocator, "abcabcabcabc", &set, 'Z', "aZZaZZaZZaZZ");
	// set = bitset("ab");
	// test_string_replace_none("string_replace_none() : 2", allocator, "abcabcabcabc", &set, 'Z', "abZabZabZabZ");
	// set = bitset("abc");
	// test_string_replace_none("string_replace_none() : 3", allocator, "abcabcabcabc", &set, 'Z', "abcabcabcabc");
	// set = bitset("");
	// test_string_replace_none("string_replace_none() : 4", allocator, "abcabcabcabc", &set, 'Z', "ZZZZZZZZZZZZ");

	// test_string_replace_predicate("string_replace_predicate() : 1", allocator, "abcdef", is_lower, 'Z', "ZZZZZZ");
	// test_string_replace_predicate("string_replace_predicate() : 2", allocator, "TTTabcdef", is_upper, 'Z', "ZZZabcdef");
	// test_string_replace_predicate("string_replace_predicate() : 3", allocator, "a1b2c3d4", is_digit, ' ', "a b c d ");

	// test_string_replace_sequence("string_replace_sequence() : 1", allocator, "" , "", "", "");
	// test_string_replace_sequence("string_replace_sequence() : 2", allocator, "this is a string this is a string this is a string" , "this", "This", "This is a string This is a string This is a string");

	allocator->deinit(allocator);
}

int main(void)
{
	call_test();

	return (0);
}
