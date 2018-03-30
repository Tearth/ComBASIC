#include "generator.h"

string* generator_build(ast_node* root)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	return code;
}