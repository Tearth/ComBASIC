#include "generator-let.h"

void generator_let_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	ast_node* name = root->children.data[0];
	ast_node* value = root->children.data[1];

	generator_expression_build(code, value, symbol_table);

	sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", name->value.data);
	string_append_s(code, buffer);
}