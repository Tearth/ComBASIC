/**
* @file generator-let.h
* @brief LET asm generator.
*
* @code
* 10 LET x = 1 + 2 * 3
* @endcode
* is translated to
* @code
* _10:
*     push	ebp
*     mov 	ebp, esp
*     mov 	eax, 1
*     push	eax
*     mov 	eax, 2
*     push	eax
*     mov 	eax, 3
*     push	eax
*     mov 	eax, [ebp - 8]
*     mov 	ebx, [ebp - 12]
*     imul	ebx
*     push	eax
*     mov 	eax, [ebp - 4]
*     mov 	ebx, [ebp - 16]
*     add 	eax, ebx
*     mov 	esp, ebp
*     pop 	ebp
*     mov 	[x], eax
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"

/**
* @brief Generates asm code for the LET AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_let_build(string* code, ast_node* root, vector* symbol_table);