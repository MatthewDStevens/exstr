/*
 * exstr.h
 *
 * Main header file for libexstr. Must be included for basic functionality.
 *
 *  Created on: Jul 1, 2016
 *      Author: Matthew Stevens
 */

#ifndef EXSTR_H
#define EXSTR_H

#include <stddef.h>
#include <stdbool.h>

#if __STDC__ == 1
	#if __STDC_VERSION__ >= 201112L
		#define exstr_strcpy(source, dest) _Generic((source), \
				exstr *: exstr_copy((source), (dest)), \
				char *: exstr_copy_string((source), (dest)))
		#define exstr_strinsert(source, dest, index) _Generic((source), \
				exstr *: exstr_insert((source), (dest), (index)), \
				char *: exstr_insert_string((source), (dest), (index)), \
				char: exstr_insert_char((source), (dest), (index)))
		#define exstr_strcat(source, dest) _Generic((source), \
				exstr *: exstr_append((source), (dest)), \
				char *: exstr_append_string((source), (dest)), \
				char: exstr_append_char((source), (dest)))
		#define exstr_strcmp(str1, str2) _Generic((str2), \
				exstr *: exstr_compare((str1), (str2)), \
				char *: exstr_compare_string((str1), (str2)))
	#elif __STDC_VERSION__ < 199901L
		#error "libexstr must be compiled with C99 or above"
	#endif
#else
	#error "libexstr must be compiled under a C standard"
#endif

// Dynamic string definition
// TODO: Consider buffer in string and realloc struct as a whole
typedef struct {
	size_t length;
	size_t capacity; // TODO: For future allocation schemes
	char *str;
	char null_term; // TODO: Safety mechanism
} exstr;

// Construction functions -----------------------------------------------------

/**
 * Initializes an exstr object to a length. If length == 0, an appropriate length is chosen.
 *
 * str: object to initialize
 * length: length to initialize str to
 *
 * return: true if successful, false otherwise
 */
bool exstr_init(exstr *str, size_t length);

/**
 * Creates a new exstr object initialized to a specified length. If length == 0, an appropriate length is chosen.
 *
 * length: length to initialize new object to
 *
 * return: pointer to new exstr object, NULL on failure
 */
exstr *exstr_new(size_t length);

/**
 * Creates a new exstr object from a character array.
 *
 * source: C style character array to copy from
 *
 * return: pointer to new exstr object, NULL on failure
 */
exstr *exstr_from_string(const char * const source);

// Copy functions -------------------------------------------------------------

/**
 * Clones an exstr object.
 *
 * source: source exstr to copy from
 *
 * return: clone of source, null on error
 */
exstr *exstr_clone(const exstr * const source);

/**
 * Copies data from an exstr object.
 *
 * source: source exstr object to copy from
 * dest: destination exstr object to copy to
 *
 * return: true on success, false otherwise
 */
bool exstr_copy(const exstr * const source, exstr * const dest);

/**
 * Copies data from a C style string.
 *
 * source: C stye string to copy from
 * dest: destination exstr opbjec to copy to
 *
 * return: true on success, false otherwise
 */
bool exstr_copy_string(const char * const source, exstr * const dest);

// Addition functions ---------------------------------------------------------

/**
 * Inserts at an index.
 *
 * source: source of string to insert
 * dest: destination to insert to
 * index: index at which to insert string
 *
 * return: true on success, false otherwise
 */
bool exstr_insert(const exstr * const source, exstr * const dest, size_t index);

/**
 * Inserts at an index.
 *
 * source: source of string to insert
 * dest: destination to insert to
 * index: index at which to insert string
 *
 * return: true on success, false otherwise
 */
bool exstr_insert_string(const char * const source, exstr * const dest, size_t index);

/**
 * Inserts at an index.
 *
 * source: source of string to insert
 * dest: destination to insert to
 * index: index at which to insert string
 *
 * return: true on success, false otherwise
 */
bool exstr_insert_char(const char source, exstr * const dest, size_t index);

/**
 * Appends to the end.
 *
 * source: source of string to append
 * dest: destination to append to
 *
 * return: true on success, false otherwise
 */
bool exstr_append(const exstr * const source, exstr * const dest);

/**
 * Appends to the end.
 *
 * source: source of string to append
 * dest: destination to append to
 *
 * return: true on success, false otherwise
 */
bool exstr_append_string(const char * const source, exstr * const dest);

/**
 * Appends to the end.
 *
 * source: source of string to append
 * dest: destination to append to
 *
 * return: true on success, false otherwise
 */
bool exstr_append_char(const char source, exstr * const dest);

// Subtraction functions ------------------------------------------------------

/**
 * Deletes a single index.
 *
 * str: string to modify
 * index: index to delete at
 *
 * return: true on success, false otherwise
 */
bool exstr_delete_at(exstr * const str, size_t index);

/**
 * Deletes a range of indices.
 *
 * str: string to modify
 * fromindex: index to start deletion at
 * toindex: index to stop deletion at (exclusively)
 *
 * return: true on success, false otherwise
 */
bool exstr_delete_range(exstr * const str, size_t fromindex, size_t toindex);

// Comparison functions -------------------------------------------------------

/**
 * Compares two strings. A the left string is less than the right string
 * if and only if the value of the character in the left string at the index
 * where the two strings first differ is less than the character in the right
 * string or (in a similar way), the left string is shorter than the right.
 *
 * str1: left string
 * str2: right string
 *
 * return: the difference between the two strings at the first different character
 */
int exstr_compare(const exstr * const str1, const exstr * const str2);

/**
 * Compares two strings. A the left string is less than the right string
 * if and only if the value of the character in the left string at the index
 * where the two strings first differ is less than the character in the right
 * string or (in a similar way), the left string is shorter than the right.
 *
 * str1: left string
 * str2: right string
 *
 * return: the difference between the two strings at the first different character
 */
int exstr_compare_string(const exstr * const str1, const char * const str2);

// Destruction functions ------------------------------------------------------

/**
 * Frees an exstr object.
 *
 * str: object to be freed
 */
void exstr_free(exstr *str);

#endif //EXSTR_H
