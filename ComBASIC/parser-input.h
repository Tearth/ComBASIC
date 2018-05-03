/**
* @file parser-input.h
* @brief INPUT parser. Displays string prompt and reads numbers from the console to the specified variables.
*
* Syntax:
* @code
* INPUT string; variable1, variable2, variable3
* @endcode
*
* AST:
* @code
* [line number]
*   -> [INPUT keyword]
*        -> [variable1]
*        -> [variable2]
*        -> [variable3]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-block.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return True if the INPUT statement is valid, otherwise false.
*/
bool parser_input_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);