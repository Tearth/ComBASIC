/**
* @file parser-for.h
* @brief FOR ... TO ... STEP ... NEXT parser. Loops the instruction block until the expression is less than 
		 condition (step is greater than 0) or the expression is greater than the condition (if step 
		 is less than 0). Default step is 1.
*
* Syntax:
* @code
* FOR variable = expression1 TO expression2
*	instructions block
* NEXT
*
* FOR variable = expression1 TO expression2 STEP expression3
*	instructions block
* NEXT
* @endcode
*
* AST:
* @code
* [line number]
*   -> [FOR keyword]
*        -> [initial assign]
*			  -> [variable]
			  -> [expression1]
		 -> [expression2]
		 -> [expression3, optional]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-node.h"
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
* @return True if the FOR statement is valid, otherwise false.
*/
bool parser_for_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);

/**
* @brief Gets the vector of tokens which are contained in FOR body (instruction block).
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @return Vector of tokens contained in FOR body.
*/
vector* parser_for_buildbody(vector* tokens, int* index, lexical_token* line_number);