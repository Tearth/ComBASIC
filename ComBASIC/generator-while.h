/**
* @file generator-while.h
* @brief WHILE asm generator.
*
* @code
* 10 WHILE x > 5
* 20 PRINT x
* 30 WEND
* @endcode
* is translated to
* @code
* _10:
*   _beginwhile_label0:
*   push	ebp
*   mov 	ebp, esp
*   mov 	eax, [x]
*   push	eax
*   mov 	eax, 5
*   push	eax
*   mov 	eax, [ebp-4]
*   mov 	ebx, [ebp-8]
*   cmp 	eax, ebx
*   mov 	eax, 1
*   jg  	_expression_label0
*   mov 	eax, 0
* _expression_label0:
*   mov 	esp, ebp
*   pop 	ebp
*   cmp 	eax, 0
*   jz  	_endwhile_label0
* _20:
*   push	ebp
*   mov 	ebp, esp
*   mov 	eax, [x]
*   mov 	esp, ebp
*   pop 	ebp
*   push	eax
*   call	_printnumber
*   push	10
*   call	_printchar
*   jmp 	_beginwhile_label0
* _endwhile_label0:
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"
#include "generator-block.h"

/**
* @brief Generates asm code for the WHILE AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_while_build(string* code, ast_node* root, vector* symbol_table);