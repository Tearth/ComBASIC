/**
* @file parser-goto.h
* @brief GOTO parser. Jumps to the specified line.
*
* Syntax:
* @code
* GOTO line number
* @endcode
*
* AST:
* @code
* [line number]
*   -> [GOTO keyword]
*        -> [line number]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return True if the GOTO statement is valid, otherwise false.
*/
bool parser_goto_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);