#include "parser-string.h"

bool parser_string_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* token = tokens->data[*index];

	if (token->token_type != T_STRING) return false;

	symbol_node* string_symbol = symboltable_add(symbol_table, S_STRING, "", token->value.data);

	ast_node* string_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(string_node, N_VARIABLE, string_symbol->name.data);

	vector_add(&keyword->children, string_node);
	(*index)++;

	return true;
}