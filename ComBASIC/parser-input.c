#include "parser-input.h"

bool parser_input_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];
	if (current_token->token_type != T_STRING) return false;
	
	parser_string_build(tokens, keyword, index, symbol_table);

	current_token = tokens->data[*index];
	if (current_token->token_type == T_NO_NEWLINE || current_token->token_type == T_COMMA)
	{
		ast_node* separator_node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(separator_node, -1, "");

		separator_node->type = current_token->token_type == T_NO_NEWLINE ? N_NONEWLINE : N_COMMA;
		vector_add(&keyword->children, separator_node);
	}
	else
	{
		printf("ERROR: no separator between input message and variable.\n");
		exit(-1);
	}

	current_token = tokens->data[++(*index)];
	if (current_token->token_type != T_IDENTIFIER) return false;

	ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(variable_node, current_token->token_type, current_token->value.data);

	vector_add(&keyword->children, variable_node);
	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");
	
	current_token = tokens->data[++(*index)];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}