#include "generator-gosub.h"

void generator_gosub_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	ast_node* line_number = root->children.data[0];

	sprintf_s(buffer, 128, "\tcall\t_%s\n", line_number->value.data);
	string_append_s(code, buffer);
}