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

	for (int i = 1; i < root->children.count; i++)
	{
		ast_node* variable = root->children.data[i];

		string_append_s(code, "\tcall\t_readnumber\n");
		sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", variable->value.data);

		string_append_s(code, buffer);
	}
}