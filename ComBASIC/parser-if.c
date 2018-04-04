#include "parser-if.h"

bool parser_if_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	ast_node* expression_node = parser_expression_build(tokens, keyword, index, symbol_table);
	vector_add(&keyword->children, expression_node);

	lexical_token* current_token = tokens->data[*index];
	if (current_token->token_type != T_KEYWORD && strcmp("THEN", current_token->value.data) != 0) return false;

	current_token = tokens->data[++(*index)];
	if (current_token->token_type != T_END_OF_INSTRUCTION) return false;

	current_token = tokens->data[++(*index)];

	vector block_tokens;
	vector_init(&block_tokens);

	while (!(current_token->token_type == T_KEYWORD && strcmp("END IF", current_token->value.data) == 0))
	{
		vector_add(&block_tokens, current_token);
		current_token = tokens->data[++(*index)];
	}

	vector_remove(&block_tokens, block_tokens.count - 1);

	ast_node* true_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(true_node, N_ROOT, "");

	parser_block_build(&block_tokens, true_node, symbol_table);
	vector_add(&keyword->children, true_node);

	current_token = tokens->data[++(*index)];
	if (current_token->token_type != T_END_OF_INSTRUCTION) return false;

	return true;
}