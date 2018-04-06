#include "code-builder.h"

string* code_build(ast_node* root, vector* symbol_table)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	code_includesection(code, root, symbol_table);
	code_datasection(code, root, symbol_table);
	code_textsection(code, root, symbol_table);
	code_endsection(code, root, symbol_table);

	return code;
}

void code_includesection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "%include 'io.asm'\n");
	string_append_s(code, "\n");
}

void code_datasection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "section .data\n");

	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* symbol = symbol_table->data[i];
		char buffer[128];

		switch (symbol->type)
		{
			case S_INTEGER:
			{
				sprintf_s(buffer, 128, "\t%s\tDD\t%s\n", symbol->name.data, "0");
				string_append_s(code, buffer);

				break;
			}
			case S_STRING:
			{
				sprintf_s(buffer, 128, "%s:\n", symbol->name.data);
				string_append_s(code, buffer);

				sprintf_s(buffer, 128, "\tdb\t'%s'\n", symbol->value.data);
				string_append_s(code, buffer);

				sprintf_s(buffer, 128, "%s_end:\n", symbol->name.data);
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
	string_append_s(code, "\n");
	string_append_s(code, "_main:\n");
	string_append_s(code, "\tmov \tebp, esp\n");

	generator_block_build(code, root, symbol_table);
}

void code_endsection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "\n");
	string_append_s(code, "\tcall\t_exit\n");
}