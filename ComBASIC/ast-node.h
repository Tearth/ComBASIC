/**
* @file ast-node.h
* @brief AST node is just a simple node (or leaf) in AST. It contains its type, value and vector of children.
*/

#pragma once
#include "string.h"
#include "vector.h"

/**
* @brief The list of ast node types.
*/
typedef enum ast_node_type
{
	N_ABS,
	N_ADD,
	N_AND,
	N_CLS,
	N_COMMA,
	N_DIV,
	N_ELSE,
	N_END,
	N_ENDIF,
	N_EQUAL,
	N_EQUAL_GREATERTHAN,
	N_EQUAL_LESSTHAN,
	N_EXPRESSION,
	N_FOR,
	N_GOTO,
	N_GOSUB,
	N_GREATERTHAN,
	N_IF,
	N_INPUT,
	N_LESSTHAN,
	N_LET,
	N_LINENUMBER,
	N_MOD,
	N_MUL,
	N_SEMICOLON,
	N_NOTEQUAL,
	N_NUMBER,
	N_OR,
	N_PRINT,
	N_REM,
	N_RETURN,
	N_RND,
	N_SUB,
	N_TIME,
	N_VARIABLE,
	N_WAIT,
	N_WEND,
	N_WHILE,
	N_ROOT
} ast_node_type;

/**
* @brief The structure which contains data about ast node like type, value (line number, variable name, ...), value.
*/
typedef struct ast_node
{
	/**
	* @brief The AST node type.
	*/
	ast_node_type type;

	/**
	* @brief The AST node value.
	*/
	string value;

	/**
	* @brief The AST node children (empty if leaf).
	*/
	vector children;
} ast_node;

/**
* @brief Inits the AST node based on the passed parameters.
* @param node The AST node to init.
* @param type AST node type.
* @param value The AST node value.
*/
void astnode_init(ast_node* node, ast_node_type type, const char* value);

/**
* @brief Clears all AST.
* @param node AST to clear.
*/
void astnode_clear(ast_node* node);