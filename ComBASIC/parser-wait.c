#include "parser-wait.h"

bool parser_wait_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table)
{
	// Time to wait (in milliseconds)
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_expression(current_token)) return false;

	vector_add(&keyword->children, parser_expression_build(tokens, index, line_number, symbol_table));

	current_token = tokens->data[*index];
	return parser_expect_endofinstruction(current_token);
}