#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

ast_node* parser_expression_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);