/**
* @file code-builder.h
* @brief Represents a set of functions to generate output asm file.
*/

#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "symbol-node.h"
#include "generator-block.h"

/**
* @brief Generates output asm code for the specified AST root.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
* @return Pointer to the output asm string.
*/
string* code_build(ast_node* root, vector* symbol_table);

/**
* @brief Generates include asm section code which contains all external asm files with helper functions.
* @param code The output asm string.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void code_includesection(string* code, ast_node* root, vector* symbol_table);

/**
* @brief Generates data asm section code which contains all global variables used in the program.
* @param code The output asm string.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void code_datasection(string* code, ast_node* root, vector* symbol_table);

/**
* @brief Generates text asm section code which contains program instructions.
* @param code The output asm string.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void code_textsection(string* code, ast_node* root, vector* symbol_table);

/**
* @brief Generates end asm section code which contains instructions called at the program end.
* @param code The output asm string.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void code_endsection(string* code, ast_node* root, vector* symbol_table);