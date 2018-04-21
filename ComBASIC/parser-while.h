/**
* @file parser-while.h
* @brief WHILE ... WEND parser. Loops the instruction block until the specified expression is true.
*
* Syntax:
* @code
* WHILE expression
*	instruction block
* WEND
* @endcode
*
* AST:
* @code
* [line number]
*   -> [WHILE keyword]
*        -> [expression]
*        -> [instruction block]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-expression.h"
#include "parser-block.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return True if the WHILE statement is valid, otherwise false.
*/
bool parser_while_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);

/**
* @brief Gets the vector of tokens which are contained in WHILE body (instruction block).
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @return Vector of tokens contained in WHILE body.
*/
vector* parser_while_buildbody(vector* tokens, int* index);