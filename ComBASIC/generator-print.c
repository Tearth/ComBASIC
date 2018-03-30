#include "generator-print.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	sprintf(buffer, "\tpush\t%s\n", root->value.data);
	string_append_s(code, buffer);

	sprintf(buffer, "\tpush\t(%s_end - %s)\n", root->value.data, root->value.data);
	string_append_s(code, buffer);

	string_append_s(code, "\tcall\t_printstring\n");
}