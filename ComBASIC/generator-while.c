#include "generator-while.h"

int while_labels_count = 0;

void generator_while_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	int current_while_labels_count = while_labels_count++;

	sprintf_s(buffer, 128, "_beginwhile_label%d:\n", current_while_labels_count);
	string_append_s(code, buffer);

	generator_expression_build(code, root->children.data[0], symbol_table);
	string_append_s(code, "\tcmp \teax, 0\n");

	sprintf_s(buffer, 128, "\tjz  \t_endwhile_label%d\n", current_while_labels_count);
	string_append_s(code, buffer);

	generator_block_build(code, root->children.data[1], symbol_table);

	sprintf_s(buffer, 128, "\tjmp \t_beginwhile_label%d\n", current_while_labels_count);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_endwhile_label%d:\n", current_while_labels_count);
	string_append_s(code, buffer);
}