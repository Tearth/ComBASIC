#include "parser-keyword.h"

ast_node* parser_keyword_build(vector* tokens, int* index)
{
	token* token = tokens->data[*index];
	if (token->token_type != T_KEYWORD) return NULL;

	ast_node* keyword_token = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(keyword_token, -1, "");

	if		(strcmp("CLS", token->value.data) == 0)		keyword_token->type = N_CLS;
	else if (strcmp("PRINT", token->value.data) == 0)	keyword_token->type = N_PRINT;
	else if (strcmp("REM", token->value.data) == 0)		keyword_token->type = N_REM;
	else if (strcmp("LET", token->value.data) == 0)		keyword_token->type = N_LET;

	(*index)++;
	return keyword_token;
}