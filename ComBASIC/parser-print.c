#include "parser-print.h"

bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	while (!parser_expect_endofinstruction(tokens->data[*index]))
	{
		if (parser_expect_string(current_token))
		{
			parser_string_build(tokens, keyword, index, symbol_table);
		}
		else if (parser_expect_expression(current_token))
		{
			ast_node* expression_node = parser_expression_build(tokens, index, symbol_table);
			vector_add(&keyword->children, expression_node);
		}

		current_token = tokens->data[*index];
		if (parser_expect_special(current_token, T_SEMICOLON) || parser_expect_special(current_token, T_COMMA))
		{
			ast_node* separator_node = (ast_node*)malloc(sizeof(ast_node));
			astnode_init(separator_node, 0, "");
			
			switch (current_token->token_type)
			{
				case T_SEMICOLON:	{ separator_node->type = N_SEMICOLON; break; }
				case T_COMMA:		{ separator_node->type = N_COMMA; break; }
			}

			vector_add(&keyword->children, separator_node);
			(*index)++;
		}

		current_token = tokens->data[*index];
	}

	return true;
}