#include "generator-if.h"

int if_labels_count = 0;

void generator_if_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	int current_if_labels_count = if_labels_count++;

	generator_expression_build(code, root->children.data[0], symbol_table);
	string_append_s(code, "\tcmp \teax, 0\n");

	sprintf_s(buffer, 128, "\tjz  \t_elsebody_label%d\n", current_if_labels_count);
	string_append_s(code, buffer);

	generator_block_build(code, root->children.data[1], symbol_table);

	sprintf_s(buffer, 128, "\tjmp \t_endif_label%d\n", current_if_labels_count);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_elsebody_label%d:\n", current_if_labels_count);
	string_append_s(code, buffer);

	if (root->children.count == 3)
	{
		generator_block_build(code, root->children.data[2], symbol_table);
	}

	sprintf_s(buffer, 128, "_endif_label%d:\n", current_if_labels_count);
	string_append_s(code, buffer);
}