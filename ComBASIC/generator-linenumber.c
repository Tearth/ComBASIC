#include "generator-linenumber.h"

void generator_linenumber_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	sprintf_s(buffer, 128, "_%s:\n", root->value.data);
	string_append_s(code, buffer);
}