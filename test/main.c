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
	printf("test : -> %s%-32s%s : ", YELLOW, name, RESET);
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

void test_string_starts_with_sequence(char *case_name, char *source, char *needle,  bool expected)
{
	bool got;

	test_setup(case_name);
	got = string_starts_with_sequence(source, needle);
	put_result(got == expected);
	test_teardown((char *) __PRETTY_FUNCTION__, case_name, " expected %s%s%s  got %s%b%s\n", GREEN, expected, RESET, RED, got, RESET);
}


void call_test(void)
{
	t_bitset set = bitset("abc");

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
	test_string_contains_predicate("string_contains_predicate() : 1", "abcdefHIJKLmnopqrstuvwxyz", is_upper, 26, true);
	test_string_contains_predicate("string_contains_predicate() : 2", "ABCDEFhijklMNOPQRSTUVWXYZ", is_lower, 26, true);
	test_string_contains_predicate("string_contains_predicate() : 3", "ABCDEFhijklMNOPQRSTUVWXYZ", is_spaces, 26, false);
	test_string_contains_sequence("string_contains_sequence() : 1", "abcdefhijklmnopqrstuvwxyz", "z", 26, true);
	test_string_contains_sequence("string_contains_sequence() : 2", "abcdefhijklmnopqrstuvwxyz", "a", 26, true);
	test_string_contains_sequence("string_contains_sequence() : 3", "abcdefhijklmnopqrstuvwxyz", "abcdefhijklmnopqrstuvwxyz", 26, true);

	test_string_starts_with_scalar("string_starts_with_scalar() : 1", "abcdef", 'a', true);
	test_string_starts_with_scalar("string_starts_with_scalar() : 2", "abcdef", 'b', false);
	test_string_starts_with_scalar("string_starts_with_scalar() : 3", "abcdef", '7', false);

	set = bitset("abc");
	test_string_starts_with_any("string_starts_with_any() : 1", "abcdef", &set, true);
	test_string_starts_with_any("string_starts_with_any() : 2", "bbcdef", &set, true);
	test_string_starts_with_any("string_starts_with_any() : 3", "cbcdef", &set, true);
	test_string_starts_with_any("string_starts_with_any() : 4", "Zbcdef", &set, false);
	test_string_starts_with_any("string_starts_with_any() : 5", "Ibcdef", &set, false);
	test_string_starts_with_any("string_starts_with_any() : 6", "Gbcdef", &set, false);

	set = bitset("ABC");
	test_string_starts_with_none("string_starts_with_none() : 1", "abcdef", &set, true);
	test_string_starts_with_none("string_starts_with_none() : 2", "bbcdef", &set, true);
	test_string_starts_with_none("string_starts_with_none() : 3", "cbcdef", &set, true);
	test_string_starts_with_none("string_starts_with_none() : 4", "Abcdef", &set, false);
	test_string_starts_with_none("string_starts_with_none() : 5", "Bbcdef", &set, false);
	test_string_starts_with_none("string_starts_with_none() : 6", "Cbcdef", &set, false);

	test_string_starts_with_predicate("string_starts_with_predicate : 1", "abcdef", is_alpha, true);
	test_string_starts_with_predicate("string_starts_with_predicate : 2", "abcdef", is_digit, false);
}

int main(void)
{
	call_test();

	return (0);
}
