#include "generator-for.h"

int for_labels_count = 0;

void generator_for_build(string* code, ast_node* root, vector* symbol_table)
{
	char buffer[128];
	int current_for_labels_count = for_labels_count++;

	ast_node* index_assignment_node = root->children.data[0];
	ast_node* index_variable_node = index_assignment_node->children.data[0];
	ast_node* index_expression_node = index_assignment_node->children.data[1];

	ast_node* index_condition_node = root->children.data[1];
	ast_node* index_step_node = root->children.count == 4 ? root->children.data[2] : NULL;

	ast_node* body_node = root->children.count == 4 ? root->children.data[3] : root->children.data[2];

	// Initial index assign
	generator_expression_build(code, index_expression_node, symbol_table);
	
	sprintf_s(buffer, 128, "\tmov \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_beginfor_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);

	// Index condition check
	if (index_step_node == NULL) string_append_s(code, "\tmov \teax, 1\n");
	else generator_expression_build(code, index_step_node, symbol_table);

	// Push step value (will be used during index updateing)
	string_append_s(code, "\tpush\teax\n");

	string_append_s(code, "\tcmp \teax, 0\n");

	// Check if negative step and jump if necessary
	sprintf_s(buffer, 128, "\tjl  \t_negcondfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	// Positive step condition
	generator_expression_build(code, index_condition_node, symbol_table);

	sprintf_s(buffer, 128, "\tcmp \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjg  \t_endfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjmp \t_forbody_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	// Negative step condition
	sprintf_s(buffer, 128, "_negcondfor_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);

	generator_expression_build(code, index_condition_node, symbol_table);

	sprintf_s(buffer, 128, "\tcmp \t[%s], eax\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjl  \t_endfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	// FOR body 
	sprintf_s(buffer, 128, "_forbody_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);

	generator_block_build(code, body_node, symbol_table);

	// Update index value
	sprintf_s(buffer, 128, "\tmov \tecx, [%s]\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	string_append_s(code, "\tpop \teax\n");

	string_append_s(code, "\tadd \tecx, eax\n");

	sprintf_s(buffer, 128, "\tmov \t[%s], ecx\n", index_variable_node->value.data);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "\tjmp \t_beginfor_label%d\n", current_for_labels_count);
	string_append_s(code, buffer);

	sprintf_s(buffer, 128, "_endfor_label%d:\n", current_for_labels_count);
	string_append_s(code, buffer);
}