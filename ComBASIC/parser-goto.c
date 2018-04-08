#include "parser-goto.h"

bool parser_goto_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	lexical_token* current_token = tokens->data[*index];
	if (current_token->token_type != T_NUMBER) return false;

	ast_node* linenumber_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(linenumber_node, N_VARIABLE, current_token->value.data);

	vector_add(&keyword->children, linenumber_node);
	
	current_token = tokens->data[++(*index)];
	return current_token->token_type == T_END_OF_INSTRUCTION;
}