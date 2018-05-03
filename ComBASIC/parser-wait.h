/**
* @file parser-wait.h
* @brief WAIT parser. Pauses the program for the specified milliseconds number.	
*
* Syntax:
* @code
* WAIT expression
* @endcode
*
* AST:
* @code
* [line number]
*   -> [WAIT keyword]
*        -> [expression]
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
* @return True if the WAIT statement is valid, otherwise false.
*/
bool parser_wait_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);