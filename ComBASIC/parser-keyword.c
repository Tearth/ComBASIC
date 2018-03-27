#include "parser-keyword.h"

node* parser_keyword_build(vector* tokens, int* index)
{
	token* token = tokens->data[*index];
	if (token->token_type != T_KEYWORD) return NULL;

	node* keyword_token = (node*)malloc(sizeof(node));
	astnode_init(keyword_token);

	if		(strcmp("CLS", token->value.data) == 0)		keyword_token->node_type = N_CLS;
	else if (strcmp("PRINT", token->value.data) == 0)	keyword_token->node_type = N_PRINT;
	else if (strcmp("REM", token->value.data) == 0)		keyword_token->node_type = N_REM;

	(*index)++;
	return keyword_token;
}