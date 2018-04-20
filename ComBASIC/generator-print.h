/**
* @file generator-print.h
* @brief PRINT asm generator.
*
* @code
* 10 PRINT "test", x
* @endcode
* is translated to
* @code
* _10:
*   push	var0
*   push	(var0_end - var0)
*   call	_printstring
*   push	10
*   call	_printchar
*   push	ebp
*   mov 	ebp, esp
*   mov 	eax, [x]
*   mov 	esp, ebp
*   pop 	ebp
*   push	eax
*   call	_printnumber
*   push	10
*   call	_printchar
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"

/**
* @brief Generates asm code for the PRINT AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_print_build(string* code, ast_node* root, vector* symbol_table);