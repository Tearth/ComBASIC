#pragma once
/**
* @file generator-block.h
* @brief Instruction block asm generator.
*/

#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-cls.h"
#include "generator-end.h"
#include "generator-for.h"
#include "generator-goto.h"
#include "generator-gosub.h"
#include "generator-if.h"
#include "generator-input.h"
#include "generator-let.h"
#include "generator-linenumber.h"
#include "generator-print.h"
#include "generator-rem.h"
#include "generator-return.h"
#include "generator-wait.h"
#include "generator-while.h"

/**
* @brief Generates asm code for the instruction block AST.
* @param code The pointer to the output asm code.
* @param root The AST root to translate into asm code.
* @param symbol_table Symbol table.
*/
void generator_block_build(string* code, ast_node* root, vector* symbol_table);