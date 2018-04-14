#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-utils.h"

bool parser_return_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);