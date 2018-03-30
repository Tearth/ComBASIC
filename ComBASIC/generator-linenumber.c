#include "generator-linenumber.h"

string* generator_linenumber_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	sprintf(buffer, "%s:\n", root->value);
	string_append_s(code, buffer);
}