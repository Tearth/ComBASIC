#include "generator-end.h"

void generator_end_build(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "\tcall\t_exit\n");
}