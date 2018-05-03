#include "parser-return.h"

bool parser_return_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table)
{
	return parser_expect_endofinstruction(tokens->data[*index]);
}