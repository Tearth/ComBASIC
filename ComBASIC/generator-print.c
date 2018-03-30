#include "generator-print.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	if (root->children.count > 0)
	{	
		ast_node* str = root->children.data[0];

		sprintf_s(buffer, 128, "\tpush\t%s\n", str->value.data);
		string_append_s(code, buffer);

		sprintf_s(buffer, 128, "\tpush\t(%s_end - %s)\n", str->value.data, str->value.data);
		string_append_s(code, buffer);

		string_append_s(code, "\tcall\t_printstring\n");
	}

	if (root->children.count != 2)
	{
		sprintf_s(buffer, 128, "\tpush\t%d\n", 10);
		string_append_s(code, buffer);

		string_append_s(code, "\tcall\t_printchar\n");
	}
}