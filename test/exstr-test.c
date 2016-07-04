/*
 * Test file for use with the libexstr library.
 */

#include "../src/exstr.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// TODO: Do testing on the extraneous conditions

static void print_test_failed() {
	fputs("...[ ]", stdout);
}

static void print_test_passed() {
	fputs("...[X]", stdout);
}

static bool verify_integrity(exstr *str) {
	// Check for length and capacity stupidity
	if (str->length >= str->capacity) {
		printf("Length/Capacity error: \n\tlength: %zu\n\tcapacity%zu: %zu\n", str->length, str->capacity);
		return false;
	}

	// Check if string is not null
	if (str->str == NULL) {
		printf("String was NULL\n");
		return false;
	}

	return true;
}

static bool test_lifecycle() {
	// Testing exstr_new
	exstr *str1 = exstr_new(10);
	printf("Initializing string using exstr_new()\n");
	if (!verify_integrity(str1)) {
		print_test_failed();
		return false;
	}
	if (str1->length != 10) {
		print_test_failed();
		return false;
	}
	print_test_passed();

	// Testing exstr_init
	printf("Initializing string using exstr_init()\n");
	exstr str2;
	exstr_init(&str2, 0);
	if (!verify_integrity(&str2)) {
		print_test_failed();
		return false;
	}
	if (str2.length == 0) {
		print_test_failed();
		return false;
	}
	print_test_passed();

	// Testing exstr_from_string
	printf("Initializing string using exstr_from_string()\n");
	const char *test_string = "This is just a test string, do not be alarmed.";
	exstr *str3 = exstr_from_string(test_string);
	if (!verify_integrity(str3)) {
		print_test_failed();
		return false;
	}
	if (str3->length != strlen(test_string)) {
		print_test_failed();
		return false;
	}
	if (strcmp(test_string, str3->str) != 0) {
		print_test_failed();
		return false;
	}
	print_test_passed();

	// Let's kill some strings
	// Testing exstr_free()
	printf("Deleting string using exstr_delete()\n");
	exstr_free(str1);
	exstr_free(NULL);
	print_test_passed();

	// Testing exstr_clear()
	printf("Clearing string using exstr_clear()\n");
	exstr_clear(&str2);
	if (!verify_integrity(&str2)) {
		print_test_failed();
		return false;
	}
	if (str2.length != 0) {
		print_test_failed();
		return false;
	}
	if (strcmp("", str2.str) != 0) {
		print_test_failed();
		return false;
	}
	print_test_passed();

	// Testing exstr_zero()
	printf("Zeroing string using exstr_zero()\n");
	exstr_zero(str3);
	if (!verify_integrity(str3)) {
		print_test_failed();
		return false;
	}
	if (strcmp("", str3->str) != 0) {
		print_test_failed();
		return false;
	}
	print_test_passed();

	return true;
}

int main(int argc, char **argv) {
	test_lifecycle();

	return 0;
}
