/**
* @file parser-linenumber.h
* @brief Line number parser.
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-utils.h"

/**
* @brief Creates and returns the line number AST node.
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @return The line number AST node.
*/
ast_node* parser_linenumber_build(vector* tokens, int* index);