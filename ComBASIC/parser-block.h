#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

#include "parser-linenumber.h"
#include "parser-keyword.h"
#include "parser-cls.h"
#include "parser-print.h"
#include "parser-rem.h"

bool parser_block_build(vector* tokens, ast_node* root, vector* symbol_table);
bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);