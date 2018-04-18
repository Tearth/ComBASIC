/**
* @file vector.h
* @brief Simple implementation of the C++ vector with all basic methods to manage structure.
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>

/**
* @brief An vector structure which contains all stored data and some additional info like allocated list size of items count.
*/
typedef struct vector
{
	/**
	* @brief The dynamic array of stored items.
	*/
	void** data;

	/**
	* @brief The max items count for the current allocated list.
	*/
	int size;

	/**
	* @brief The current items count.
	*/
	int count;
} vector;

/**
* @brief Inits the vector structure to the default values.
* @param vector Vector structure to init.
*/
void vector_init(vector* vector);

/**
* @brief Adds an item to the specified vector structure at the end of the internal list.
* @param vector Vector structure to init.
* @param data The item to add.
*/
void vector_add(vector* vector, void* data);

/**
* @brief Inserts an item to the specified vector structure at the specified index.
* @param vector Vector structure where new item will be stored.
* @param data The item to add.
* @param index Item index where will be stored.
*/
void vector_insert(vector* vector, void* data, int index);

/**
* @brief Removes an item with the specified index in the specified vector structure.
* @param vector Vector structure to init.
* @param index Item index.
*/
void vector_remove(vector* vector, int index);

/**
* @brief Clears the vector structure by removing all items from the internal list. Note that the items must be
	     manually free, otherwise there will be memory leak.
* @param vector Vector structure to clear.
*/
void vector_clear(vector* vector);
