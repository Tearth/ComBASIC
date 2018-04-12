#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "parser-block.h"

ast_node* ast_build(vector* tokens, vector* symbol_table);

void ast_dump(ast_node* node);
void ast_dump_r(ast_node* node, int level);
void ast_clear(ast_node* node);
