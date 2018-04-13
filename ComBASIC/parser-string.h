#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-utils.h"

bool parser_string_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);