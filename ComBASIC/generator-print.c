#include "generator-print.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	if (root->children.count == 0)
	{
		string_append_s(code, "\tpush\t10\n");
		string_append_s(code, "\tcall\t_printchar\n");
	}
	else
	{	
		for (int i = 0; i < root->children.count; i++)
		{
			ast_node* argument_to_display = root->children.data[i];
			switch (argument_to_display->type)
			{
				case N_VARIABLE:
				{
					sprintf_s(buffer, 128, "\tpush\t%s\n", argument_to_display->value.data);
					string_append_s(code, buffer);

					sprintf_s(buffer, 128, "\tpush\t(%s_end - %s)\n", argument_to_display->value.data, argument_to_display->value.data);
					string_append_s(code, buffer);

					string_append_s(code, "\tcall\t_printstring\n");
					break;
				}

				case N_EXPRESSION:
				{
					generator_expression_build(code, argument_to_display, symbol_table);

					string_append_s(code, "\tpush\teax\n");
					string_append_s(code, "\tcall\t_printnumber\n");
					break;
				}

				case N_SEMICOLON:
				{
					break;
				}

				case N_COMMA:
				{
					string_append_s(code, "\tpush\t10\n");
					string_append_s(code, "\tcall\t_printchar\n");

					break;
				}
			}
		}

		ast_node* last_child = root->children.data[root->children.count - 1];
		if (last_child->type != N_SEMICOLON)
		{
			string_append_s(code, "\tpush\t10\n");
			string_append_s(code, "\tcall\t_printchar\n");
		}
	}
}