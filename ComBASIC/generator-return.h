/**
* @file generator-return.h
* @brief RETURN asm generator.
*
* @code
* 10 RETURN
* @endcode
* is translated to
* @code
* _10:
*   ret
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the RETURN AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_return_build(string* code, ast_node* root, vector* symbol_table);