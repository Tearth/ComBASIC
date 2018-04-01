#include "code-builder.h"

string* code_build(ast_node* root, vector* symbol_table)
{
	string* code = (string*)malloc(sizeof(string));
	string_init(code);

	code_datasection(code, root, symbol_table);
	code_textsection(code, root, symbol_table);
	code_endsection(code, root, symbol_table);

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
	string_append_s(code, "\t%include\t'io.asm'\n");
	string_append_s(code, "\n");
	string_append_s(code, "_main:\n");
	string_append_s(code, "\tmov \tebp, esp\n");

	for (int i = 0; i < root->children.count; i++)
	{
		ast_node* linenumber_node = root->children.data[i];
		generator_linenumber_build(code, linenumber_node, symbol_table);

		ast_node* keyword_node = linenumber_node->children.data[0];
		switch (keyword_node->type)
		{
			case N_CLS: { generator_cls_build(code, keyword_node, symbol_table); break; }
			case N_PRINT: { generator_print_build(code, keyword_node, symbol_table); break; }
			case N_REM: { generator_rem_build(code, keyword_node, symbol_table); break; }
		}
	}
}

void code_endsection(string* code, ast_node* root, vector* symbol_table)
{
	string_append_s(code, "\tcall\tExitProcess\n");
}