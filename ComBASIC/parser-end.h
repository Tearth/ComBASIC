/**
* @file parser-end.h
* @brief END parser. Ends program and exits the console.
*
* Syntax:
* @code
* END
* @endcode
*
* AST:
* @code
* [line number]
*   -> [END keyword]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @param symbol_table Symbol table.
* @return True if the END statement is valid, otherwise false.
*/
bool parser_end_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);