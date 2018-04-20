/**
* @file generator-for.h
* @brief FOR asm generator.
*
* @code
* 10 FOR x = 1 TO 2 + 3
* 20 PRINT "x"
* 30 NEXT
* @endcode
* is translated to
* @code
* _10:
*     push	ebp
*     mov 	ebp, esp
*     mov 	eax, 1
*     mov 	esp, ebp
*     pop 	ebp
*     mov 	[x], eax
* _beginfor_label0:
*     mov 	eax, 1
*     push	eax
*     cmp 	eax, 0
*     jl  	_negcondfor_label0
*     push	ebp
*     mov 	ebp, esp
*     mov 	eax, 2
*     push	eax
*     mov 	eax, 3
*     push	eax
*     mov 	eax, [ebp-4]
*     mov 	ebx, [ebp-8]
*     add 	eax, ebx
*     mov 	esp, ebp
*     pop 	ebp
*     cmp 	[x], eax
*     jg  	_endfor_label0
*     jmp 	_forbody_label0
* _negcondfor_label0:
*     push	ebp
*     mov 	ebp, esp
*     mov 	eax, 2
*     push	eax
*     mov 	eax, 3
*     push	eax
*     mov 	eax, [ebp-4]
*     mov 	ebx, [ebp-8]
*     add 	eax, ebx
*     mov 	esp, ebp
*     pop 	ebp
*     cmp 	[x], eax
*     jl  	_endfor_label0
* _forbody_label0:
* _20:
*     push	var0
*     push	(var0_end - var0)
*     call	_printstring
*     push	10
*     call	_printchar
*     mov 	ecx, [x]
*     pop 	eax
*     add 	ecx, eax
*     mov 	[x], ecx
*     jmp 	_beginfor_label0
* _endfor_label0:
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"
#include "generator-block.h"

/**
* @brief Generates asm code for the FOR AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_for_build(string* code, ast_node* root, vector* symbol_table);