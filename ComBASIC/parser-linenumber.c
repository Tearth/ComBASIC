#include "parser-linenumber.h"

node* parser_linenumber_build(vector* tokens, int* index)
{
	token* token = tokens->data[*index];
	if (token->token_type != T_NUMBER) return NULL;

	node* linenumber_token = (node*)malloc(sizeof(node));
	ast_initnode(linenumber_token);

	linenumber_token->node_type = N_LINENUMBER;
	linenumber_token->node_value = token->value;

	(*index)++;
	return linenumber_token;
}