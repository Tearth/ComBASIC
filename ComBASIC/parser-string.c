#include "parser-string.h"

bool parser_string_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	token* token = tokens->data[*index];

	if (token->token_type != T_STRING) return false;

	ast_node* string_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(string_node);

	string_node->type = N_VARIABLE;
	vector_add(&keyword->children, string_node);

	symbol_node* string_symbol = (symbol_node*)malloc(sizeof(symbol_node));
	symbolnode_init(string_symbol);
	string_symbol->type = S_STRING;
	string_append_s(&string_symbol->value, token->value.data);
	symboltable_add(symbol_table, string_symbol);

	string_append_s(&string_node->value, string_symbol->name.data);
	(*index)++;

	return true;
}