/*
 * exstr.c
 *
 * Main source file for libexstr.
 *
 *  Created on: Jul 1, 2016
 *      Author: Matthew Stevens
 */

#include "exstr.h"
#include <string.h>
//TODO: Conditional Linux library includes
//TODO: Conditional Windows library includes

#define DEFAULT_LENGTH 128

/**
 * Black boxes the capacity calculation.
 */
static inline size_t get_capacity(const size_t length) {
	return length;
}

/**
 * Frees the str member if not null.
 */
static inline void clear_data(const exstr * const str) {
	if (str->str != NULL) {
		free(str->str);
	}
}

_Bool exstr_init(exstr *str, const size_t length) {
	// Set length and capacity
	if (length == 0) {
		// TODO: Come up with better default
		str->length = DEFAULT_LENGTH;
	}
	else {
		str->length = length;
	}
	str->capacity = get_capacity(str->length);

	// Allocate space for string
	str->str = (char *)malloc(str->capacity * sizeof(char)); // TODO: More efficient allocation (higher size, using OS specific functions
	if (str->str == NULL) {
		return 0;
	}

	str->null_term = '\0';
	return 1;
}


exstr *exstr_new(const size_t length) {
	// Allocate new exstr
	exstr *str = (exstr *)malloc(sizeof(exstr));
	if (str == NULL) {
		return NULL;
	}

	// Set length and capacity
	if (length == 0) {
		// TODO: Come up with better default
		str->length = DEFAULT_LENGTH;
	}
	else {
		str->length = length;
	}
	str->capacity = get_capacity(str->length);

	// Allocate space for string
	str->str = (char *)malloc(str->capacity * sizeof(char));
	if (str->str == NULL) {
		free(str);
		return NULL;
	}

	// Set null terminator
	str->null_term = '\0';

	return str;
}

exstr *exstr_from_string(const char * const source) {
	size_t source_length;

	// Cannot initialize from NULL
	if (source == NULL) {
		return NULL;
	}

	// Allocate exstr object
	exstr *str = (exstr *)malloc(sizeof(exstr));
	if (str == NULL) {
		return NULL;
	}

	// Get length and capacity
	source_length = strlen(source);
	str->length = source_length;
	str->capacity = get_capacity(source_length);

	// Allocate space for string
	str->str = (char *)malloc((str->length + 1) * sizeof(char));
	if (str->str == NULL) {
		free(str);
		return NULL;
	}

	// Copy ar
	strcpy(str->str, source);

	// Set null terminator
	str->null_term = '\0';

	return str;
}

exstr *exstr_clone(const exstr * const source) {
	// Can't clone NULL
	if (source == NULL) {
		return NULL;
	}

	// Allocate exstr object
	exstr *str = (exstr *)malloc(sizeof(exstr));
	if (str == NULL) {
		return NULL;
	}

	// Shallow copy primitive members
	str->length = source->length;
	str->capacity = source->capacity;
	str->null_term = '\0';

	// Deep copy other parts
	if (str->str != NULL) {
		free(str->str);
	}
	str->str = (char *)malloc(str->capacity * sizeof(char));
	if (str->str == NULL) {
		free(str);
		return NULL;
	}
	strcpy(str->str, source->str);

	return str;
}

_Bool exstr_copy(const exstr * const source, exstr * const dest) {
	// Shallow copy primitive members
	dest->length = source->length;
	dest->capacity = source->capacity;
	dest->null_term = '\0';

	// Deep copy other parts
	clear_data(dest);
	dest->str = (char *)malloc(dest->capacity * sizeof(char));
	if (dest->str == NULL) {
		return 0;
	}
	strcpy(dest->str, source->str);

	return 1;
}

_Bool exstr_copy_string(const char * const source, exstr * const dest) {
	size_t source_length;

	// Cannot initialize from NULL
	if (source == NULL) {
		return NULL;
	}

	// Get length and capacity
	source_length = strlen(source);
	dest->length = source_length;
	dest->capacity = get_capacity(source_length);

	// Allocate space for string
	clear_data(dest);
	dest->str = (char *)malloc(dest->capacity * sizeof(char));
	if (dest->str == NULL) {
		return 0;
	}

	// Copy string
	strcpy(dest->str, source);

	return 1;
}

void exstr_free(exstr *str) {
	free(str->str);
	free(str);
}
