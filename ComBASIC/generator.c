#include "generator.h"

string* generator_build(ast_node* root, vector* symbol_table)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	string_append_s(code, "Hello\nWorld!");

	return code;
}