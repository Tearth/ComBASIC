#include "parser-print.h"

bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];
	if (parser_expect_string(current_token))
	{
		parser_string_build(tokens, keyword, index, symbol_table);
	}
	else if (parser_expect_expression(current_token))
	{
		ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
		vector_add(&keyword->children, expression_node);
	}

	current_token = tokens->data[*index];
	if (parser_expect_special(current_token, T_NO_NEWLINE))
	{
		ast_node* nonewline_node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(nonewline_node, N_NONEWLINE, "");

		vector_add(&keyword->children, nonewline_node);
		(*index)++;
	}

	current_token = tokens->data[*index];
	return parser_expect_endofinstruction(current_token);
}