#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "symbol-node.h"
#include "parser-utils.h"

ast_node* parser_expression_build(vector* tokens, int* index, vector* symbol_table);
vector* parser_expression_buildrpn(vector* tokens, int* index, vector* symbol_table);
vector* parser_expression_buildrpnnodes(vector* rpn, vector* symbol_table);
void parser_expression_buildrpntree(vector* rpn_nodes, ast_node* expression_root);

bool parser_expression_istokenvalid(lexical_token* token);
bool parser_expression_isparenthesis(lexical_token* token);
int parser_expression_getpriority(lexical_token* token);
int parser_expression_getargumentscount(ast_node_type node_type);