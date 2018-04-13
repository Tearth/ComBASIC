#include "parser-if.h"

bool parser_if_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	// Expression
	ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
	vector_add(&keyword->children, expression_node);

	// THEN keyword
	lexical_token* current_token = tokens->data[*index];
	if (!parser_expect_keyword(current_token, "THEN")) return false;
	
	current_token = tokens->data[++(*index)];
	if (!parser_expect_endofinstruction(current_token)) return false;

	// IF body
	vector* body_tokens = parser_if_buildbody(tokens, index);

	ast_node* ifbody_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(ifbody_node, N_ROOT, "");

	parser_block_build(body_tokens, ifbody_node, symbol_table);
	vector_add(&keyword->children, ifbody_node);

	vector_clear(body_tokens);
	free(body_tokens);

	current_token = tokens->data[*index];

	// ELSE body
	if (parser_expect_keyword(current_token, "ELSE"))
	{
		current_token = tokens->data[++(*index)];
		if (!parser_expect_endofinstruction(current_token)) return false;

		vector* else_tokens = parser_if_buildelse(tokens, index);

		ast_node* elsebody_node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(elsebody_node, N_ROOT, "");

		parser_block_build(else_tokens, elsebody_node, symbol_table);
		vector_add(&keyword->children, elsebody_node);

		vector_clear(else_tokens);
		free(else_tokens);
	}

	current_token = tokens->data[++(*index)];
	return parser_expect_endofinstruction(current_token);
}

vector* parser_if_buildbody(vector* tokens, int* index)
{
	vector* block_tokens = (vector*)malloc(sizeof(vector));
	vector_init(block_tokens);

	int if_balance = 1;
	lexical_token* current_token = tokens->data[++(*index)];

	while (if_balance > 0 && ++(*index) < tokens->count)
	{
		vector_add(block_tokens, current_token);
		current_token = tokens->data[*index];

		if (current_token->token_type == T_KEYWORD)
		{
			if (strcmp("IF", current_token->value.data) == 0)		if_balance++;
			if (strcmp("END IF", current_token->value.data) == 0)	if_balance--;
			if (strcmp("ELSE", current_token->value.data) == 0)		if_balance--;
		}
	}

	if (if_balance != 0)
	{
		printf("ERROR: Invalid IF statement");
		exit(-1);
	}

	vector_remove(block_tokens, block_tokens->count - 1);
	return block_tokens;
}

vector* parser_if_buildelse(vector* tokens, int* index)
{
	vector* block_tokens = (vector*)malloc(sizeof(vector));
	vector_init(block_tokens);

	int if_balance = 1;
	lexical_token* current_token = tokens->data[++(*index)];

	while (if_balance > 0 && ++(*index) < tokens->count)
	{
		vector_add(block_tokens, current_token);
		current_token = tokens->data[*index];

		if (current_token->token_type == T_KEYWORD)
		{
			if (strcmp("IF", current_token->value.data) == 0)		if_balance++;
			if (strcmp("END IF", current_token->value.data) == 0)	if_balance--;
		}
	}

	if (if_balance != 0)
	{
		printf("ERROR: Invalid IF statement");
		exit(-1);
	}

	vector_remove(block_tokens, block_tokens->count - 1);
	return block_tokens;
}