#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "parser-linenumber.h"
#include "parser-keyword.h"
#include "parser-cls.h"
#include "parser-print.h"
#include "parser-rem.h"

ast_node* ast_build(vector* tokens, vector* symbol_table);

bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);
void ast_dump(ast_node* node);
void ast_dump_r(ast_node* node, int level);
void ast_clean(ast_node* node);