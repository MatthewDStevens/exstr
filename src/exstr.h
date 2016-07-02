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

//TODO: Shoud define own size_t?
//TODO: use ifdef for C11, use type generic macros for type induction
//TODO: Wide string and/or UTF-8/16/32 support
//TODO: Consider extracting into functions and sacrificing performance

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
_Bool exstr_init(exstr *str, const size_t length);

/**
 * Creates a new exstr object initialized to a specified length. If length == 0, an appropriate length is chosen.
 *
 * length: length to initialize new object to
 *
 * return: pointer to new exstr object, NULL on failure
 */
exstr *exstr_new(const size_t length);

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
_Bool exstr_copy(const exstr * const source, exstr * const dest);

/**
 * Copies data from a C style string.
 *
 * source: C stye string to copy from
 * dest: destination exstr opbjec to copy to
 *
 * return: true on success, false otherwise
 */
_Bool exstr_copy_string(const char * const source, exstr * const dest);


// Destruction functions ------------------------------------------------------

/**
 * Frees an exstr object.
 *
 * str: object to be freed
 */
void exstr_free(exstr *str);

#endif //EXSTR_H
