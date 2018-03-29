#include "parser-linenumber.h"

ast_node* parser_linenumber_build(vector* tokens, int* index)
{
	token* token = tokens->data[*index];
	if (token->token_type != T_NUMBER) return NULL;

	ast_node* linenumber_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(linenumber_node);

	linenumber_node->type = N_LINENUMBER;
	string_append_s(&linenumber_node->value, token->value.data);

	(*index)++;
	return linenumber_node;
}