/**
* @file generator-if.h
* @brief IF asm generator.
*
* @code
* 10 IF 1 = 1 THEN
* 20 PRINT "Yes"
* 30 ELSE
* 40 PRINT "No"
* 50 END IF
* @endcode
* is translated to
* @code
* _10:
*    push	ebp
*    mov 	ebp, esp
*    mov 	eax, 1
*    push	eax
*    mov 	eax, 1
*    push	eax
*    mov 	eax, [ebp-4]
*    mov 	ebx, [ebp-8]
*    cmp 	eax, ebx
*    mov 	eax, 0
*    jne	_expression_label0
*    mov 	eax, 1
* _expression_label0:
*    mov 	esp, ebp
*    pop 	ebp
*    cmp 	eax, 0
*    jz  	_elsebody_label0
* _20:
*    push	var0
*    push	(var0_end - var0)
*    call	_printstring
*    push	10
*    call	_printchar
*    jmp 	_endif_label0
* _elsebody_label0:
* _40:
*    push	var1
*    push	(var1_end - var1)
*    call	_printstring
*    push	10
*    call	_printchar
* _endif_label0:
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-block.h"

/**
* @brief Generates asm code for the IF AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_if_build(string* code, ast_node* root, vector* symbol_table);