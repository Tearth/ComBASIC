/**
* @file generator-cls.h
* @brief CLS asm generator.
*
* @code
* 10 CLS
* @endcode
* is translated to
* @code
* _10:
*     call _clear
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the CLS AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_cls_build(string* code, ast_node* root, vector* symbol_table);