/**
* @file parser-if.h
* @brief IF ... THEN ... ELSE ... END IF parser. Checks if the specified expression is true and jumps 
*		 to the body (or else if exists) if possible.
*
* Syntax:
* @code
* IF expression THEN
*     instructions block 1
* END IF
*
* IF expression THEN
* instructions block 1
* ELSE
* instructions block 2
* END IF
* @endcode
*
* AST:
* @code
* [line number]
*   -> [IF keyword]
*        -> [expression]
*        -> [instruction block 1]
*        -> [instruction block 2]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-block.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passed vector of tokens.
* @param tokens The vector of tokens to parse.
* @param keyword The AST node with WHILE keyword.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @param symbol_table Symbol table.
* @return True if the IF statement is valid, otherwise false.
*/
bool parser_if_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);

/**
* @brief Gets the vector of tokens which are contained in IF body (instruction block).
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @return Vector of tokens contained in IF body.
*/
vector* parser_if_buildbody(vector* tokens, int* index, lexical_token* line_number);

/**
* @brief Gets the vector of tokens which are contained in IF else-body (instruction block).
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @return Vector of tokens contained in IF else-body.
*/
vector* parser_if_buildelse(vector* tokens, int* index, lexical_token* line_number);