#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

bool parser_end_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);