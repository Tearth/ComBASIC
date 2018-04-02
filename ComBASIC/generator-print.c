#include "generator-print.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	if (root->children.count > 0)
	{	
		ast_node* argument_to_display = root->children.data[0];
		if (argument_to_display->type == N_VARIABLE)
		{
			sprintf_s(buffer, 128, "\tpush\t%s\n", argument_to_display->value.data);
			string_append_s(code, buffer);

			sprintf_s(buffer, 128, "\tpush\t(%s_end - %s)\n", argument_to_display->value.data, argument_to_display->value.data);
			string_append_s(code, buffer);

			string_append_s(code, "\tcall\t_printstring\n");
		}
		else
		{
			generator_expression_build(code, argument_to_display, symbol_table);

			string_append_s(code, "\tpush\teax\n");
			string_append_s(code, "\tcall\t_printnumber\n");
		}
	}

	if (root->children.count != 2)
	{
		string_append_s(code, "\tpush\t10\n");
		string_append_s(code, "\tcall\t_printchar\n");
	}
}