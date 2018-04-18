/**
* @file ast-builder.h
* @brief AST (Abstract Syntax Tree) is a tree representation of tokens which has been generated during the
		 lexical analysis. During AST generating, compiler checks if syntax is correct for the BASIC language,
		 updates symbol table and finally returns the root node which contains all parsed source code.
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "parser-block.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param symbol_table Symbol table.
* @return The pointer to the root of the built AST.
*/
ast_node* ast_build(vector* tokens, vector* symbol_table);

/**
* @brief Prints the AST in a tree form.
* @param node AST root.
*/
void ast_dump(ast_node* node);

/**
* @brief Recursive helper to ast_dump function. Prints the AST in a tree form.
* @param node AST root.
* @param level Level of the currently printed node.
*/
void ast_dump_r(ast_node* node, int level);

/**
* @brief Clears AST recursively. Note that the items must be
*	     manually free, otherwise there will be memory leak.
* @param node AST root.
*/
void ast_clear(ast_node* node);
