#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-block.h"

bool parser_if_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);