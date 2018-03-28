#include "parser-print.h"

bool parser_print_build(vector* tokens, node* keyword, int* index, vector* symbol_table)
{
	token* end_of_instruction_token;
	token* token = tokens->data[*index];

	if (token->token_type != T_STRING) return false;

	node* string_node = (node*)malloc(sizeof(node));
	astnode_init(string_node);

	string_node->node_type = N_VARIABLE;
	string_append_s(&string_node->node_value, "test");
	vector_add(&keyword->children, string_node);

	symbol* string_symbol = (symbol*)malloc(sizeof(symbol));
	symboltable_init(string_symbol);
	string_append_s(&string_symbol->name, "test");
	string_symbol->type = S_STRING;
	string_append_s(&string_symbol->value, token->value.data);
	symboltable_add(symbol_table, string_symbol);

	(*index)++;

	end_of_instruction_token = tokens->data[*index];
	if (end_of_instruction_token->token_type != T_END_OF_INSTRUCTION) return false;

	return true;
}