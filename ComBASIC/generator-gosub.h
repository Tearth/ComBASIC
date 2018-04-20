/**
* @file generator-gosub.h
* @brief GOSUB asm generator.
*
* @code
* 10 GOSUB 1200
* @endcode
* is translated to
* @code
* _10:
*     call _1200
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the GOSUB AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_gosub_build(string* code, ast_node* root, vector* symbol_table);