#include "parser-let.h"

bool parser_let_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	if (current_token->token_type != T_IDENTIFIER)
	{
		printf("ERROR: No variable with LET.\n");
		exit(-1);
	}

	ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(variable_node, N_VARIABLE, current_token->value.data);
	
	vector_add(&keyword->children, variable_node);

	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

	(*index)++;
	current_token = tokens->data[*index];

	if (current_token->token_type != T_OPERATOR || strcmp("=", current_token->value.data) != 0)
	{
		printf("ERROR: No equal operator with LET.\n");
		exit(-1);
	}

	(*index)++;
	current_token = tokens->data[*index];

	if (parser_expression_istokenvalid(current_token))
	{
		ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
		vector_add(&keyword->children, expression_node);
	}
	else
	{
		printf("ERROR: Invalid expression.\n");
		exit(-1);
	}

	current_token = tokens->data[*index];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}