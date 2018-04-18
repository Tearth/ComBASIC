/**
* @file parser-cls.h
* @brief CLS parser. Clears the console and moves cursor position to the begin.	
*
* Syntax:
* @code
* CLS
* @endcode
*
* AST:
* @code
* [line number]
*   -> [CLS keyword]
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
* @param symbol_table Symbol table.
* @return True if the CLS statement is valid, otherwise false.
*/
bool parser_cls_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);