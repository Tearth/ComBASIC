/**
* @file parser-string.h
* @brief String parser.
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-utils.h"

ast_node* parser_string_build(vector* tokens, int* index, vector* symbol_table);