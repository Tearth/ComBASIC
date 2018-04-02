#include "parser-print.h"

bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	token* current_token = tokens->data[*index];
	if (current_token->token_type == T_STRING)
	{
		parser_string_build(tokens, keyword, index, symbol_table);

		current_token = tokens->data[*index];
		if (current_token->token_type == T_NO_NEWLINE)
		{
			ast_node* nonewline_node = (ast_node*)malloc(sizeof(ast_node));
			astnode_init(nonewline_node, N_NONEWLINE, "");

			vector_add(&keyword->children, nonewline_node);
			(*index)++;
		}
	}
	else if (parser_expression_istokenvalid(current_token))
	{
		ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
		vector_add(&keyword->children, expression_node);
	}

	current_token = tokens->data[*index];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}