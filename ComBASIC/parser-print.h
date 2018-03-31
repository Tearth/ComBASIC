#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "parser-string.h"
#include "parser-expression.h"

bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);