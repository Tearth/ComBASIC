#include "parser-let.h"

bool parser_let_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];

	// Variable that will have assigned new value
	if (!parser_expect_identifier(current_token)) return false;

	ast_node* variable_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(variable_node, N_VARIABLE, current_token->value.data);
	vector_add(&keyword->children, variable_node);

	symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

	// = operator
	current_token = tokens->data[++(*index)];
	if (!parser_expect_operator(current_token, "=")) return false;

	// Expression
	current_token = tokens->data[++(*index)];
	if (!parser_expect_expression(current_token)) return false;

	vector_add(&keyword->children, parser_expression_build(tokens, keyword, index, symbol_table));

	current_token = tokens->data[*index];
	return parser_expect_endofinstruction(current_token);
}