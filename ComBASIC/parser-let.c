#include "parser-let.h"

ast_node* parser_let_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	token* current_token = tokens->data[*index];

	if (current_token->token_type != T_IDENTIFIER)
	{
		printf("ERROR: No variable with LET.");
		exit(-1);
	}

	ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(variable_node);

	variable_node->type = N_LINENUMBER;
	string_append_s(&variable_node->value, current_token->value.data);
	
	vector_add(&keyword->children, variable_node);

	symbol_node* variable_symbol = (symbol_node*)malloc(sizeof(symbol_node));
	symbolnode_init(variable_symbol);

	variable_symbol->type = S_INTEGER;
	string_append_s(&variable_symbol->name, current_token->value.data);
	string_append_s(&variable_symbol->value, "0");

	symboltable_add(symbol_table, variable_symbol);

	(*index)++;
	current_token = tokens->data[*index];

	if (current_token->token_type != T_OPERATOR || strcmp("=", current_token->value.data) != 0)
	{
		printf("ERROR: No equal operator with LET.");
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
		printf("ERROR: Invalid expression.");
		exit(-1);
	}

	current_token = tokens->data[*index];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}