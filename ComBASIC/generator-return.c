#include "generator-return.h"

void generator_return_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	sprintf_s(buffer, 128, "\tret\n");
	string_append_s(code, buffer);
}