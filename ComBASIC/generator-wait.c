#include "generator-wait.h"

void generator_wait_build(string* code, ast_node* root, vector* symbol_table)
{
	generator_expression_build(code, root->children.data[0], symbol_table);

	string_append_s(code, "\tpush\teax\n");
	string_append_s(code, "\tcall\t_wait\n");
}