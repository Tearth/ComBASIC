/**
* @file parser-gosub.h
* @brief GOSUB ... RETURN parser. Stores the current instruction address onto stack and jumps to 
		 the specified line. When enters the RETURN, resumes program at the line after GOSUB instruction 
		 using the address from the stack.	
*
* Syntax:
* @code
* GOSUB line number
* ...
* instruction block
* RETURN
* @endcode
*
* AST:
* @code
* [line number]
*   -> [GOSUB keyword]
*        -> [line number]
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
* @return True if the GOSUB statement is valid, otherwise false.
*/
bool parser_gosub_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);