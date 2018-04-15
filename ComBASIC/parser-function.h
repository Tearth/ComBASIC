#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "symbol-node.h"
#include "parser-utils.h"

ast_node* parser_function_build(vector* tokens, int* index, vector* symbol_table);
void parser_function_getarguments(vector* tokens, ast_node* function, int* index, vector* symbol_table);
int parser_function_getargumentscount(ast_node_type node_type);