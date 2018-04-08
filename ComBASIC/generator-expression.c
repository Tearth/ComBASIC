#include "generator-expression.h"

int expression_labels_count = 0;

void generator_expression_build(string* code, ast_node* root, vector* symbol_table)
{
	if (root->type == N_EXPRESSION) root = root->children.data[0];

	int stack_pointer = 4;
	generator_expression_build_r(code, root, &stack_pointer, symbol_table);

	string_append_s(code, "\tmov \tesp, ebp\n");
}

void generator_expression_build_r(string* code, ast_node* root, int* stack_pointer, vector* symbol_table)
{
	char buffer[128];

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
				string_append_s(code, "\timul\tebx\n");
				break;
			}

			case N_DIV:
			{
				string_append_s(code, "\tcdq\n");
				string_append_s(code, "\tidiv\tebx\n");
				break;
			}

			case N_MOD:
			{
				string_append_s(code, "\tcdq\n");
				string_append_s(code, "\tidiv\tebx\n");
				string_append_s(code, "\tmov \teax, edx\n");
				break;
			}

			case N_EQUAL:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "\tjne  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_NOTEQUAL:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjne  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_GREATERTHAN:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjg  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_EQUAL_GREATERTHAN:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjge  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_LESSTHAN:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjl  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_EQUAL_LESSTHAN:
			{
				string_append_s(code, "\tcmp \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjle  \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_AND:
			{
				string_append_s(code, "\tand \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjnz \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			case N_OR:
			{
				string_append_s(code, "\tor  \teax, ebx\n");
				string_append_s(code, "\tmov \teax, 1\n");

				sprintf_s(buffer, 128, "\tjnz \t_expression_label%d\n", expression_labels_count);
				string_append_s(code, buffer);

				string_append_s(code, "\tmov \teax, 0\n");

				sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
				string_append_s(code, buffer);

				expression_labels_count++;
				break;
			}

			default:
			{
				printf("ERROR: invalid operator");
				exit(-1);
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