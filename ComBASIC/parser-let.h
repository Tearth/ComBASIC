#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-node.h"
#include "symbol-table.h"

ast_node* parser_let_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);