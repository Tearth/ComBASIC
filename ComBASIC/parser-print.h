/**
* @file parser-print.h
* @brief PRINT parser. Prints the specified content (string or expression) to the console.
*
* Syntax:
* @code
* PRINT expression, string without new line; string with new line
* @endcode
*
* AST:
* @code
* [line number]
*   -> [PRINT keyword]
*        -> [expression1]
*        -> [semicolon]
*        -> [string1]
*        -> [comma]
*        -> [string2]
*        -> [comma]
*        -> [expression2]
* @endcode
*/


#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-string.h"
#include "parser-expression.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return True if the PRINT statement is valid, otherwise false.
*/
bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);