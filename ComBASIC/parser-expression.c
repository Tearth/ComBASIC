#include "parser-expression.h"

ast_node* parser_expression_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	ast_node* expression_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(expression_node);
	expression_node->type = N_EXPRESSION;

	return expression_node;
}