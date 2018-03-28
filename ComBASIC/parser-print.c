#include "parser-print.h"

bool parser_print_build(vector* tokens, node* keyword, int* index)
{
	token* end_of_instruction_token;
	token* token = tokens->data[*index];

	if (token->token_type != T_STRING) return false;

	node* string_node = (node*)malloc(sizeof(node));
	astnode_init(string_node);

	string_node->node_type = N_STRING;
	string_append_s(&string_node->node_value, token->value.data);
	vector_add(&keyword->children, string_node);

	(*index)++;

	end_of_instruction_token = tokens->data[*index];
	if (end_of_instruction_token->token_type != T_END_OF_INSTRUCTION) return false;

	return true;
}