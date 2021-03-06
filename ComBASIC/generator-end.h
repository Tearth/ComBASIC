/**
* @file generator-end.h
* @brief END asm generator.
*
* @code
* 10 END
* @endcode
* is translated to
* @code
* _10:
*     call _exit
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the END AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_end_build(string* code, ast_node* root, vector* symbol_table);