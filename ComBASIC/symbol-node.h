/**
* @file symbol-node.h
* @brief Represents an single node stored in the symbol table.
*/

#pragma once
#include "string.h"

/**
* @brief The list of symbol node types.
*/
typedef enum symbol_node_type
{
	S_INTEGER,
	S_STRING
} symbol_node_type;

/**
* @brief The structure which contains data about symbol node like type, name, value.
*/
typedef struct symbol_node
{
	/**
	* @brief The symbol node type.
	*/
	symbol_node_type type;

	/**
	* @brief The symbol node name.
	*/
	string name;

	/**
	* @brief The symbol node value.
	*/
	string value;
} symbol_node;

/**
* @brief Inits the symbol node based on the passed parameters. If name is empty, then it will be generated
*		 automatically (with var{x} format).
* @param symbol The vector of all symbol nodes.
* @param type Symbol node type.
* @param name Symbol node name.
* @param value Symbol node value.
*/
void symbolnode_init(symbol_node* symbol, symbol_node_type type, const char* name, const char* value);

/**
* @brief Clears the specified symbol node.
* @param symbol The symbol node to clear.
*/
void symbolnode_clear(symbol_node* symbol);
