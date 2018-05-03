#include "parser-for.h"

bool parser_for_build(vector* tokens, ast_node* keyword, int* index, lexical_token* line_number, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	// Root for index variable and initial expression
	ast_node* initial_expression_root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(initial_expression_root, N_ROOT, "");

	// Index variable
	if (!parser_expect_identifier(current_token)) return false;

	ast_node* index_variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(index_variable_node, N_VARIABLE, current_token->value.data);
	vector_add(&initial_expression_root->children, index_variable_node);

	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

	// = operator
	current_token = tokens->data[++(*index)];
	if (!parser_expect_operator(current_token, "=")) return false;

	// Initial index expression
	current_token = tokens->data[++(*index)];
	if (!parser_expect_expression(current_token)) return false;

	vector_add(&initial_expression_root->children, parser_expression_build(tokens, index, line_number, symbol_table));
	vector_add(&keyword->children, initial_expression_root);

	// TO keyword
	current_token = tokens->data[*index];
	if (!parser_expect_keyword(current_token, "TO")) return false;

	// End expression
	current_token = tokens->data[++(*index)];
	if (!parser_expect_expression(current_token)) return false;

	vector_add(&keyword->children, parser_expression_build(tokens, index, line_number, symbol_table));

	// STEP keyword
	current_token = tokens->data[*index];
	if (parser_expect_keyword(current_token, "STEP"))
	{
		current_token = tokens->data[++(*index)];
		if (!parser_expect_expression(current_token)) return false;

		vector_add(&keyword->children, parser_expression_build(tokens, index, line_number, symbol_table));
	}

	current_token = tokens->data[*index];
	if (!parser_expect_endofinstruction(current_token)) return false;

	// FOR body
	vector* body_tokens = parser_for_buildbody(tokens, index, line_number);

	ast_node* forbody_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(forbody_node, N_ROOT, "");

	parser_block_build(body_tokens, forbody_node, symbol_table);
	vector_add(&keyword->children, forbody_node);

	vector_clear(body_tokens);
	free(body_tokens);

	current_token = tokens->data[++(*index)];
	return parser_expect_endofinstruction(current_token);
}

vector* parser_for_buildbody(vector* tokens, int* index, lexical_token* line_number)
{
	vector* block_tokens = (vector*)malloc(sizeof(vector));
	vector_init(block_tokens);

	int for_balance = 1;
	lexical_token* current_token = tokens->data[++(*index)];

	while (for_balance > 0 && ++(*index) < tokens->count)
	{
		vector_add(block_tokens, current_token);
		current_token = tokens->data[*index];

		if (current_token->token_type == T_KEYWORD)
		{
			if (strcmp("FOR", current_token->value.data) == 0)		for_balance++;
			if (strcmp("NEXT", current_token->value.data) == 0)		for_balance--;
		}
	}

	if (for_balance != 0)
	{
		printf("\n\nPARSER ERROR: Invalid FOR statement at line %s: invalid NEXT keywords count.\n", line_number->value.data);
		exit(-1);
	}

	vector_remove(block_tokens, block_tokens->count - 1);
	return block_tokens;
}