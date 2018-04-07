#include "generator-for.h"

int for_labels_count = 0;

void generator_for_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	int current_for_labels_count = for_labels_count++;

	ast_node* index_assignment_node = root->children.data[0];
	ast_node* index_variable_node = index_assignment_node->children.data[0];
	ast_node* index_expression_node = index_assignment_node->children.data[1];

	generator_expression_build(code, index_expression_node, symbol_table);
	
	sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_beginfor_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);

	generator_expression_build(code, root->children.data[1], symbol_table);

	sprintf_s(buffer, 128, "\tcmp \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjg  \t_endfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	generator_block_build(code, root->children.data[2], symbol_table);

	sprintf_s(buffer, 128, "\tmov \teax, [%s]\n", index_variable_node->value.data);
	string_append_s(code, buffer);
	string_append_s(code, "\tinc \teax\n");
	sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjmp \t_beginfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_endfor_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);
}