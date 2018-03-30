#include "generator-print.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	ast_node* str = root->children.data[0];

	sprintf(buffer, "\tpush\t%s\n", str->value.data);
	string_append_s(code, buffer);

	sprintf(buffer, "\tpush\t(%s_end - %s)\n", str->value.data, str->value.data);
	string_append_s(code, buffer);

	string_append_s(code, "\tcall\t_printstring\n");
}