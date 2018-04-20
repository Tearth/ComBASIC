/**
* @file generator-linenumber.h
* @brief Line number asm generator.
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

/**
* @brief Generates asm code for the line number.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_linenumber_build(string* code, ast_node* root, vector* symbol_table);