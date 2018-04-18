/**
* @file string.h
* @brief Simple implementation of the C++ string with all basic methods to manage structure.
*/

#pragma once
#include <stdlib.h>
#include <stdbool.h>

/**
* @brief An string structure which contains text and some additional info like allocated string size and its length.
*/
typedef struct string
{
	/**
	* @brief The string array.
	*/
	char* data;

	/**
	* @brief The max length for the current allocated memory.
	*/
	int size;

	/**
	* @brief The current string length.
	*/
	int count;
} string;

/**
* @brief Inits the string structure to the default values.
* @param string String structure to init.
*/
void string_init(string* string);

/**
* @brief Duplicates the specified string structure (deep copy so both strings aren't just reference copies).
* @param original String structure to duplicate.
* @return The duplicated string structure.
*/
string* string_clone(string* original);

/**
* @brief Appends an char at the end of the specified string.
* @param string String to which the character will be added.
* @param c Char to add.
*/
void string_append_c(string* string, char c);

/**
* @brief Appends an string array at the end of the specified string.
* @param string String to which the character will be added.
* @param str String array to add.
*/
void string_append_s(string* string, const char* str);

/**
* @brief Removes last char from the specified string.
* @param string String which will have removed last char.
*/
void string_removelast(string* string);

/**
* @brief Removes all chars from the specified string (but not removes allocated memory like string_clear).
* @param string String which will be cleared.
*/
void string_removeall(string* string);

/**
* @brief Clears the string structure by removing the allocated memory for string.
* @param string String structure to clear.
*/
void string_clear(string* string);
