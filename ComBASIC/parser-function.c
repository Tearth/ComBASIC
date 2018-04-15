#include "parser-function.h"

ast_node* parser_function_build(vector* tokens, int* index, vector* symbol_table)
{
	ast_node* function_root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(function_root, N_EXPRESSION, "");

	parser_function_getarguments(tokens, function_root, index, symbol_table);

	return function_root;
}

void parser_function_getarguments(vector* tokens, ast_node* function, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_operator(current_token, "(")) return false;
}

int parser_function_getargumentscount(ast_node_type node_type)
{
	switch (node_type)
	{
		case N_ABS:		return 5;
		default:		return 2;
	}
}