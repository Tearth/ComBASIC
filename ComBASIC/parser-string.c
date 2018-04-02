#include "parser-string.h"

bool parser_string_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	token* token = tokens->data[*index];

	if (token->token_type != T_STRING) return false;

	ast_node* string_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(string_node);

	string_node->type = N_VARIABLE;
	vector_add(&keyword->children, string_node);

	symbol_node* string_symbol = symboltable_add(symbol_table, S_STRING, "", token->value.data);
	string_append_s(&string_node->value, string_symbol->name.data);
	(*index)++;

	return true;
}