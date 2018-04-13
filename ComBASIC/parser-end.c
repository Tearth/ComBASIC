#include "parser-end.h"

bool parser_end_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];
	return parser_expect_endofinstruction(current_token);
}