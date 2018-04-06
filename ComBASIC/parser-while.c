#include "parser-while.h"

bool parser_while_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
	vector_add(&keyword->children, expression_node);

	lexical_token* current_token = tokens->data[*index];
	if (current_token->token_type != T_END_OF_INSTRUCTION) return false;

	vector* body_tokens = parser_while_buildbody(tokens, index);

	ast_node* whilebody_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(whilebody_node, N_ROOT, "");

	parser_block_build(body_tokens, whilebody_node, symbol_table);
	vector_add(&keyword->children, whilebody_node);

	current_token = tokens->data[++(*index)];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}

vector* parser_while_buildbody(vector* tokens, int* index)
{
	vector* block_tokens = (vector*)malloc(sizeof(vector));
	vector_init(block_tokens);

	int while_balance = 1;
	lexical_token* current_token = tokens->data[++(*index)];

	while (while_balance > 0 && *index < tokens->count)
	{
		vector_add(block_tokens, current_token);
		current_token = tokens->data[++(*index)];

		if (current_token->token_type == T_KEYWORD)
		{
			if (strcmp("WHILE", current_token->value.data) == 0)	while_balance++;
			if (strcmp("WEND", current_token->value.data) == 0)		while_balance--;
		}
	}

	if (while_balance != 0)
	{
		printf("ERROR: Invalid WHILE statement");
		exit(-1);
	}

	vector_remove(block_tokens, block_tokens->count - 1);
	return block_tokens;
}