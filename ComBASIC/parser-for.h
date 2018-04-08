#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-node.h"
#include "symbol-table.h"
#include "parser-expression.h"
#include "parser-block.h"

bool parser_for_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);
vector* parser_for_buildbody(vector* tokens, int* index);