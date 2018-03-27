#include "parser-linenumber.h"

node* parser_linenumber_build(vector* tokens, int* index)
{
	token* token = tokens->data[*index];
	if (token->token_type != T_NUMBER) return NULL;

	node* linenumber_node = (node*)malloc(sizeof(node));
	astnode_init(linenumber_node);

	linenumber_node->node_type = N_LINENUMBER;
	linenumber_node->node_value = token->value;

	(*index)++;
	return linenumber_node;
}