#include "parser-wait.h"

bool parser_wait_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	// Time to wait (in milliseconds)
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_number(current_token)) return false;

	ast_node* linenumber_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(linenumber_node, N_VARIABLE, current_token->value.data);

	vector_add(&keyword->children, linenumber_node);

	current_token = tokens->data[++(*index)];
	return parser_expect_endofinstruction(current_token);
}