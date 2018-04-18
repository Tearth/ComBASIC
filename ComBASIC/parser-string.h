/**
* @file parser-string.h
* @brief String parser.
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-utils.h"

/**
* @brief Creates and returns the string ast node.
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @param symbol_table Symbol table.
* @return The string ast node.
*/
ast_node* parser_string_build(vector* tokens, int* index, vector* symbol_table);