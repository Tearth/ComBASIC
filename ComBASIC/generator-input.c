#include "generator-input.h"

void generator_input_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];

	ast_node* input_prompt = root->children.data[0];
	sprintf_s(buffer, 128, "\tpush\t%s\n", input_prompt->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tpush\t(%s_end - %s)\n", input_prompt->value.data, input_prompt->value.data);
	string_append_s(code, buffer);

	string_append_s(code, "\tcall\t_printstring\n");

	ast_node* input_separator = root->children.data[1];
	if(input_separator->type == N_NONEWLINE)
	{
		string_append_s(code, "\tpush\t'?'\n");
		string_append_s(code, "\tcall\t_printchar\n");

		string_append_s(code, "\tpush\t' '\n");
		string_append_s(code, "\tcall\t_printchar\n");
	}

	ast_node* input_variable = root->children.data[2];

	string_append_s(code, "\tcall\t_readnumber\n");
	sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", input_variable->value.data);

	string_append_s(code, buffer);
}