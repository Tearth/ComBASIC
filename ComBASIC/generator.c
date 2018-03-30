#include "generator.h"

string* generator_build(ast_node* root, vector* symbol_table)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	generator_datasection(code, root, symbol_table);

	return code;
}

void generator_datasection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "section .data\n");

	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* symbol = symbol_table->data[i];
		switch (symbol->type)
		{
			case S_INTEGER: break;
			case S_STRING:
			{
				char buffer[128];

				sprintf(buffer, "%s:\n\tdb\t'%s'\n%s_end:\n", symbol->name.data, symbol->value.data, symbol->name.data);
				string_append_s(code, buffer);

				break;
			}
		}
	}

	string_append_s("\n");
}