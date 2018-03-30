#include "generator-cls.h"

void generator_cls_build(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "\tcall\t_clear\n");
}