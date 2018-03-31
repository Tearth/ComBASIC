#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

ast_node* parser_expression_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);
vector* parser_expression_buildrpn(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);
bool parser_expression_istokenvalid(token* token);
bool parser_expression_isparenthesis(token* token);
int parser_expression_getpriority(token* token);