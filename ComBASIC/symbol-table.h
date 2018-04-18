/**
* @file symbol-table.h
* @brief Symbol table is an structure which contains all variables detected during syntax analysis. Because current
*		 implementation of BASIC language supports only integers and partially strings, so its only role is to generate
*		 list of them during code generation phase. More complex language stores also functions, classes etc.
*/

#pragma once
#include <string.h>
#include "symbol-node.h"
#include "vector.h"
#include "string.h"

/**
* @brief Creates a new symbol node based on the passed parameters and adds it to the symbol table. 
*		 If name is empty, then it will be generated automatically (with var{x} format).
* @param symbol_table The vector of all symbol nodes.
* @param type Symbol node type.
* @param name Symbol node name.
* @param value Symbol node value.
* @return The pointer to the newly created symbol node.
*/
symbol_node* symboltable_add(vector* symbol_table, symbol_node_type type, const char* name, const char* value);

/**
* @brief Prints all symbol nodes stored in the passed vector.
* @param symbol_table Symbol table to dump.
*/
void symboltable_dump(vector* symbol_table);


/**
* @brief Clears all symbol nodes stored in the passed vector. Note that the items must be
*	     manually free, otherwise there will be memory leak.
* @param symbol_table Symbol table to clear.
*/
void symboltable_clear(vector* symbol_table);