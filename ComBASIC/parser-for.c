#include "parser-for.h"

ast_node* parser_for_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	ast_node* initial_expression_root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(initial_expression_root, N_ROOT, "");

	if (current_token->token_type != T_IDENTIFIER)
	{
		printf("ERROR: No variable with LET.");
		exit(-1);
	}

	ast_node* index_variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(index_variable_node, N_VARIABLE, current_token->value.data);

	vector_add(&initial_expression_root->children, index_variable_node);

	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

	current_token = tokens->data[++(*index)];

	if (current_token->token_type != T_OPERATOR || strcmp("=", current_token->value.data) != 0)
	{
		printf("ERROR: No equal operator with LET.");
		exit(-1);
	}

	current_token = tokens->data[++(*index)];

	if (parser_expression_istokenvalid(current_token))
	{
		ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
		vector_add(&initial_expression_root->children, expression_node);
	}
	else
	{
		printf("ERROR: Invalid expression.");
		exit(-1);
	}

	vector_add(&keyword->children, initial_expression_root);

	current_token = tokens->data[*index];

	if (current_token->token_type != T_KEYWORD || strcmp("TO", current_token->value.data) != 0)
	{
		printf("ERROR: No TO keyword in FOR statement.");
		exit(-1);
	}

	current_token = tokens->data[++(*index)];

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
	if (current_token->token_type != T_END_OF_INSTRUCTION) return false;

	vector* body_tokens = parser_for_buildbody(tokens, index);

	ast_node* forbody_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(forbody_node, N_ROOT, "");

	parser_block_build(body_tokens, forbody_node, symbol_table);
	vector_add(&keyword->children, forbody_node);

	vector_clean(body_tokens);
	free(body_tokens);

	current_token = tokens->data[++(*index)];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}

vector* parser_for_buildbody(vector* tokens, int* index)
{
	vector* block_tokens = (vector*)malloc(sizeof(vector));
	vector_init(block_tokens);

	int for_balance = 1;
	lexical_token* current_token = tokens->data[++(*index)];

	while (for_balance > 0 && *index < tokens->count)
	{
		vector_add(block_tokens, current_token);
		current_token = tokens->data[++(*index)];

		if (current_token->token_type == T_KEYWORD)
		{
			if (strcmp("FOR", current_token->value.data) == 0)		for_balance++;
			if (strcmp("NEXT", current_token->value.data) == 0)		for_balance--;
		}
	}

	if (for_balance != 0)
	{
		printf("ERROR: Invalid FOR statement");
		exit(-1);
	}

	vector_remove(block_tokens, block_tokens->count - 1);
	return block_tokens;
}