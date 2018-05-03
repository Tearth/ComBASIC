#include "parser-input.h"

bool parser_input_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table)
{
	// Prompt string
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_string(current_token)) return false;
	
	ast_node* string_node = parser_string_build(tokens, index, symbol_table);
	vector_add(&keyword->children, string_node);

	current_token = tokens->data[*index];
	if (!parser_expect_special(current_token, T_SEMICOLON)) return false;

	current_token = tokens->data[++(*index)];
	while (!parser_expect_endofinstruction(tokens->data[*index]))
	{
		// Input variable
		if (!parser_expect_identifier(current_token)) return false;

		ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(variable_node, current_token->token_type, current_token->value.data);

		vector_add(&keyword->children, variable_node);
		symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

		// Separator
		current_token = tokens->data[++(*index)];
		if (parser_expect_special(current_token, T_COMMA))
		{
			(*index)++;
		}

		current_token = tokens->data[*index];
	}

	return parser_expect_endofinstruction(tokens->data[*index]);
}