#include "generator-expression.h"

int expression_labels_count = 0;

void generator_expression_build(string* code, ast_node* root, vector* symbol_table)
{
	if (root->type == N_EXPRESSION) root = root->children.data[0];

	string_append_s(code, "\tpush\tebp\n");
	string_append_s(code, "\tmov \tebp, esp\n");

	int stack_pointer = 4;
	generator_expression_build_r(code, root, &stack_pointer, symbol_table);

	string_append_s(code, "\tmov \tesp, ebp\n");
	string_append_s(code, "\tpop \tebp\n");
}

void generator_expression_build_r(string* code, ast_node* root, int* stack_pointer, vector* symbol_table)
{
	char buffer[128];

	ast_node *first, *second;
	int first_stack_pointer, second_stack_pointer;

	if (root->children.count == 2)
	{
		first = root->children.data[1];

		generator_expression_build_r(code, first, stack_pointer, symbol_table);
		string_append_s(code, "\tpush\teax\n");
		first_stack_pointer = *stack_pointer;
		(*stack_pointer) += 4;

		second = root->children.data[0];

		generator_expression_build_r(code, second, stack_pointer, symbol_table);
		string_append_s(code, "\tpush\teax\n");
		second_stack_pointer = *stack_pointer;
		(*stack_pointer) += 4;
	}
	else if (root->children.count == 1)
	{
		first = root->children.data[0];

		generator_expression_build_r(code, first, stack_pointer, symbol_table);
		string_append_s(code, "\tpush\teax\n");
		first_stack_pointer = *stack_pointer;
		(*stack_pointer) += 4;
	}

	if (root->children.count == 2)
	{
		sprintf_s(buffer, 128, "\tmov \teax, [ebp-%d]\n", first_stack_pointer);
		string_append_s(code, buffer);

		sprintf_s(buffer, 128, "\tmov \tebx, [ebp-%d]\n", second_stack_pointer);
		string_append_s(code, buffer);
	}
	else if (root->children.count == 1)
	{
		sprintf_s(buffer, 128, "\tmov \teax, [ebp-%d]\n", first_stack_pointer);
		string_append_s(code, buffer);
	}

	switch (root->type)
	{
		case N_NUMBER:
		{
			sprintf_s(buffer, 128, "\tmov \teax, %s\n", root->value.data);
			string_append_s(code, buffer);

			break;
		}

		case N_VARIABLE:
		{
			sprintf_s(buffer, 128, "\tmov \teax, [%s]\n", root->value.data);
			string_append_s(code, buffer);

			break;
		}

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

		case N_ABS:
		{
			string_append_s(code, "\tcmp \teax, 0\n");
			sprintf_s(buffer, 128, "\tjg  \t_expression_label%d\n", expression_labels_count);

			string_append_s(code, "\tneg \teax\n");

			sprintf_s(buffer, 128, "_expression_label%d:\n", expression_labels_count);
			string_append_s(code, buffer);

			expression_labels_count++;
			break;
		}

		case N_TIME:
		{
			string_append_s(code, "\tcall\t_gettime\n");
			break;
		}

		default:
		{
			printf("ERROR: invalid operator.\n");
			exit(-1);
		}
	}
}