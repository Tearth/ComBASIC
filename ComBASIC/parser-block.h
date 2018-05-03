/**
* @file parser-block.h
* @brief Instruction block parser.
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

#include "parser-linenumber.h"
#include "parser-keyword.h"
#include "parser-cls.h"
#include "parser-print.h"
#include "parser-rem.h"
#include "parser-for.h"
#include "parser-goto.h"
#include "parser-if.h"
#include "parser-input.h"
#include "parser-let.h"
#include "parser-while.h"
#include "parser-end.h"
#include "parser-gosub.h"
#include "parser-return.h"
#include "parser-wait.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the passet list of tokens.
* @param tokens The instruction block to parse.
* @param root The root of the instruction block.
* @param symbol_table Symbol table.
* @return True if the instruction block is valid, otherwise false.
*/
bool parser_block_build(vector* tokens, ast_node* root, vector* symbol_table);

/**
* @brief Builds an AST for the specified keyword.
* @param tokens The vector of tokens to parse.
* @param keyword The keyword.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return True if the keyword and its parameters were valid, otherwise false.
*/
bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table);