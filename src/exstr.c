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
#include <stdlib.h>
//TODO: Conditional Linux library includes
//TODO: Conditional Windows library includes

#define DEFAULT_LENGTH 128

/**
 * Black boxes the capacity calculation.
 */
static inline size_t get_capacity(size_t length) {
	return length + 1;
}

/**
 * Frees the str member if not null.
 */
static inline void clear_data(const exstr * const str) {
	if (str->str != NULL) {
		free(str->str);
	}
}

/**
 * Reallocates an exstr object to meet a new length.
 */
static inline bool exstr_realloc(exstr * const str, size_t length, bool force) {
	size_t new_capacity;

	// Check if we need to realloc
	if (!force && length <= str->capacity) {
		return true;
	}

	// Get new capacity
	new_capacity = get_capacity(length);

	// Realloc
	char *new_str = realloc(str->str, new_capacity);
	if (new_str != NULL) {
		str->str = new_str;
		str->capacity = new_capacity;
		return true;
	}
	return false;
}

bool exstr_init(exstr *str, size_t length) {
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
		return false;
	}

	str->null_term = '\0';
	return true;
}


exstr *exstr_new(size_t length) {
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
	memcpy(str->str, source->str, source->length + 1);

	return str;
}

bool exstr_copy(const exstr * const source, exstr * const dest) {
	// Can't copy from/to NULL
	if (source == NULL || dest == NULL) {
		return false;
	}

	// Shallow copy primitive members
	dest->length = source->length;
	dest->capacity = source->capacity;
	dest->null_term = '\0';

	// Deep copy other parts
	clear_data(dest);
	dest->str = (char *)malloc(dest->capacity * sizeof(char));
	if (dest->str == NULL) {
		return false;
	}
	memcpy(dest->str, source->str, source->length + 1);

	return true;
}

bool exstr_copy_string(const char * const source, exstr * const dest) {
	size_t source_length;

	// Cannot initialize from/to NULL
	if (source == NULL || dest == NULL) {
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
		return false;
	}

	// Copy string
	memcpy(dest->str, source, source_length + 1);

	return true;
}

/**
 * Performs insertion at an index.
 */
static inline bool exstr_insert_at(const char * const source, exstr * const dest, size_t index, size_t insert_length) {
	// Separate original contents
	memcpy(dest->str + index + insert_length, dest->str + index, dest->length - index + 1); // TODO: Check math

	// Insert new contents
	memcpy(dest->str + index, source, insert_length);

	// Update length
	dest->length += insert_length;

	return true;
}

bool exstr_insert(const exstr * const source, exstr * const dest, size_t index) {
	size_t new_length;

	// Can't insert from/to NULL or bad index
	if (source == NULL || dest == NULL || index >= dest->length) {
		return false;
	}

	// Calculate length
	new_length = source->length + dest->length;

	// Ensure space
	if (!exstr_realloc(dest, new_length + 1, 1)) {
		return false;
	}

	return exstr_insert_at(source->str, dest, index, source->length);
}

bool exstr_insert_string(const char * const source, exstr * const dest, size_t index) {
	size_t source_length;
	size_t new_length;

	// Can't insert from/to NULL or bad index
	if (source == NULL || dest == NULL || index >= dest->length) {
		return false;
	}

	// Calculate lengths
	source_length = strlen(source);
	new_length = dest->length + source_length;

	// Ensure space
	if (!exstr_realloc(dest, new_length + 1, 1)) {
		return false;
	}

	return exstr_insert_at(source, dest, index, source_length);
}

bool exstr_insert_char(const char source, exstr * const dest, size_t index) {
	// Can't insert to NULL or bad index
	if (dest == NULL || index >= dest->length) {
		return false;
	}

	// Ensure space
	if (!exstr_realloc(dest, dest->length + 2, 1)) {
		return false;
	}

	return exstr_insert_at(&source, dest, index, 1);
}

// TODO: Make append functions into macros or alter behavior?

bool exstr_append(const exstr * const source, exstr * const dest) {
	return exstr_insert(source, dest, dest->length);
}

bool exstr_append_string(const char * const source, exstr * const dest) {
	return exstr_insert_string(source, dest, dest->length);
}

bool exstr_append_char(const char source, exstr * const dest) {
	return exstr_insert_char(source, dest, dest->length);
}

bool exstr_delete_at(exstr * const str, size_t index) {
	return exstr_delete_range(str, index, index + 1);
}

bool exstr_delete_range(exstr * const str, size_t fromindex, size_t toindex) {
	// Cannot delete from NULL or bad index
	if (str == NULL || fromindex >= toindex || fromindex >= str->length || toindex > str->length) {
		return false;
	}

	// TODO: Data scrubbing
	// Overwrite data
	memcpy(str->str + fromindex, str->str + toindex, toindex - fromindex);

	return true;
}

int exstr_compare(const exstr * const str1, const exstr * const str2) {
	// Check lengths (this is nice and easy, so we optimize it)
	if (str1->length < str2->length) {
		return (int)str2->str[str1->length];
	}
	else if (str2->length < str1->length) {
		return (int)str1->str[str2->length];
	}
	else {
		int difference = 0;
		const char *str1_pos = str1->str;
		const char *str2_pos = str2->str;

		// Do the iterative approach
		for (size_t i = 0; i < str1->length; i++, str1_pos++, str2_pos++) {
			difference = *str1_pos - *str2_pos;
			if (difference != 0) {
				return difference;
			}
		}

		// Must be the same string
		return 0;
	}
}

int exstr_compare_string(const exstr * const str1, const char * const str2) {
	int difference = 0;
	const char *str1_pos = str1->str;
	const char *str2_pos = str2;

	// Do the iterative approach
	for (size_t i = 0; i < str1->length; i++, str1_pos++, str2_pos++) {
		difference = *str1_pos - *str2_pos;
		if (difference != 0) {
			return difference;
		}
	}

	// Must be the same string
	return 0;
}

void exstr_free(exstr *str) {
	// Don't even think about it, kiddo
	if (str == NULL) {
		return;
	}
	free(str->str);
	free(str);
}
