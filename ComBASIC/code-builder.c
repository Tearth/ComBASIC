#include "code-builder.h"

string* code_build(ast_node* root, vector* symbol_table)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	code_datasection(code, root, symbol_table);
	code_textsection(code, root, symbol_table);

	return code;
}

void code_datasection(string* code, ast_node* root, vector* symbol_table)
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

	string_append_s(code, "\n");
}

void code_textsection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "section .text\n");
	string_append_s(code, "\tglobal\t_main\n");
	string_append_s(code, "\t%include\t'io.asm'\n");
	string_append_s(code, "\n");
	string_append_s(code, "_main:");

	for (int i = 0; i < root->children.count; i++)
	{
		
	}
}