#include "parser-end.h"

bool parser_end_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	return parser_expect_endofinstruction(tokens->data[*index]);
}