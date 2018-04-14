#include "parser-input.h"

bool parser_input_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	// Prompt string
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_string(current_token)) return false;
	
	parser_string_build(tokens, keyword, index, symbol_table);

	// Separator
	current_token = tokens->data[*index];
	if (parser_expect_special(current_token, T_SEMICOLON) || parser_expect_special(current_token, T_COMMA))
	{
		ast_node* separator_node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(separator_node, -1, "");

		switch (current_token->token_type)
		{
			case T_SEMICOLON:	{ separator_node->type = N_SEMICOLON; break; }
			case T_COMMA:		{ separator_node->type = N_COMMA; break; }
		}

		vector_add(&keyword->children, separator_node);
	}
	else
	{
		printf("ERROR: no separator between input message and variable.\n");
		exit(-1);
	}

	// Input variable
	current_token = tokens->data[++(*index)];
	if (!parser_expect_identifier(current_token)) return false;

	ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(variable_node, current_token->token_type, current_token->value.data);

	vector_add(&keyword->children, variable_node);
	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");
	
	current_token = tokens->data[++(*index)];
	return parser_expect_endofinstruction(current_token);
}