#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"

bool parser_goto_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);