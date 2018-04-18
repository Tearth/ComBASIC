#include "parser-string.h"

ast_node* parser_string_build(vector* tokens, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	if (!parser_expect_string(current_token)) return false;

	symbol_node* string_symbol = symboltable_add(symbol_table, S_STRING, "", current_token->value.data);

	ast_node* string_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(string_node, N_VARIABLE, string_symbol->name.data);

	(*index)++;
	return string_node;
}