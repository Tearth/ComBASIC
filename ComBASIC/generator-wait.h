/**
* @file generator-wait.h
* @brief WAIT asm generator.
*
* @code
* 10 WAIT 1000 + x
* @endcode
* is translated to
* @code
* _10:
*   push	ebp
*   mov 	ebp, esp
*   mov 	eax, 1000
*   push	eax
*   mov 	eax, [x]
*   push	eax
*   mov 	eax, [ebp-4]
*   mov 	ebx, [ebp-8]
*   add 	eax, ebx
*   mov 	esp, ebp
*   pop 	ebp
*   push	eax
*   call	_wait
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"

/**
* @brief Generates asm code for the WAIT AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_wait_build(string* code, ast_node* root, vector* symbol_table);