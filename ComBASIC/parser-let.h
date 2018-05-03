/**
* @file parser-let.h
* @brief LET parser. Assigns an expression to the specified variable.
*
* Syntax:
* @code
* LET variable = expression
* @endcode
*
* AST:
* @code
* [line number]
*   -> [LET keyword]
*        -> [variable]
*        -> [expression]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-node.h"
#include "symbol-table.h"
#include "parser-expression.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @param symbol_table Symbol table.
* @return True if the LET statement is valid, otherwise false.
*/
bool parser_let_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);