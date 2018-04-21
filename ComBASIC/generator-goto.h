/**
* @file generator-goto.h
* @brief GOTO asm generator.
*
* @code
* 10 GOTO 1200
* @endcode
* is translated to
* @code
* _10:
*     jmp _1200
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the GOTO AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_goto_build(string* code, ast_node* root, vector* symbol_table);