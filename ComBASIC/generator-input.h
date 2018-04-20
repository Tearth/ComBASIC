/**
* @file generator-input.h
* @brief INPUT asm generator.
*
* @code
* 10 INPUT "Prompt: "; a, b
* @endcode
* is translated to
* @code
* _10:
*   push	var0
*   push	(var0_end - var0)
*   call	_printstring
*   call	_readnumber
*   mov 	[a], eax
*   call	_readnumber
*   mov 	[b], eax
* @endcode
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the INPUT AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_input_build(string* code, ast_node* root, vector* symbol_table);