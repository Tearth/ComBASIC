/**
* @file parser-keyword.h
* @brief Keyword parser.
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-utils.h"

/**
* @brief Creates and returns the keyword ast node.
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @return The keyword ast node.
*/
ast_node* parser_keyword_build(vector* tokens, int* index);