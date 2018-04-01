#include "generator-expression.h"

void generator_expression_build(string* code, ast_node* root, vector* symbol_table)
{
	if (root->type == N_EXPRESSION) root = root->children.data[0];

	int stack_pointer = 4;
	generator_expression_build_r(code, root, &stack_pointer, symbol_table);

	string_append_s(code, "\tmov \tesp, ebp\n");
}

void generator_expression_build_r(string* code, ast_node* root, int* stack_pointer, vector* symbol_table)
{
	if (root->children.count > 0)
	{
		ast_node* first = root->children.data[1];
		ast_node* second = root->children.data[0];

		generator_expression_build_r(code, first, stack_pointer, symbol_table);
		string_append_s(code, "\tpush\teax\n");
		int first_stack_pointer = *stack_pointer;
		(*stack_pointer) += 4;

		generator_expression_build_r(code, second, stack_pointer, symbol_table);
		string_append_s(code, "\tpush\teax\n");
		int second_stack_pointer = *stack_pointer;
		(*stack_pointer) += 4;


		char buffer[128];

		sprintf_s(buffer, 128, "\tmov \teax, [ebp-%d]\n", first_stack_pointer);
		string_append_s(code, buffer);

		sprintf_s(buffer, 128, "\tmov \tebx, [ebp-%d]\n", second_stack_pointer);
		string_append_s(code, buffer);

		switch (root->type)
		{
			case N_ADD:
			{
				string_append_s(code, "\tadd \teax, ebx\n");
				break;
			}

			case N_SUB:
			{
				string_append_s(code, "\tsub \teax, ebx\n");
				break;
			}

			case N_MUL:
			{
				sprintf_s(buffer, 128, "\timul\tebx\n");
				string_append_s(code, buffer);
				break;
			}

			case N_DIV:
			{
				string_append_s(code, "\txor \tedx, edx\n");

				sprintf_s(buffer, 128, "\tidiv\tebx\n");
				string_append_s(code, buffer);
				break;
			}
		}
	}
	else
	{
		char buffer[128];

		if (root->type == N_NUMBER)
		{
			sprintf_s(buffer, 128, "\tmov \teax, %s\n", root->value.data);
		}
		else if (root->type == N_VARIABLE)
		{
			sprintf_s(buffer, 128, "\tmov \teax, [%s]\n", root->value.data);
		}

		string_append_s(code, buffer);
	}
}