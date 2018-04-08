#include "parser-keyword.h"

ast_node* parser_keyword_build(vector* tokens, int* index)
{
	lexical_token* token = tokens->data[*index];
	if (token->token_type != T_KEYWORD) return NULL;

	ast_node* keyword_token = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(keyword_token, -1, "");

	if		(strcmp("CLS", token->value.data) == 0)		keyword_token->type = N_CLS;
	else if (strcmp("ELSE", token->value.data) == 0)	keyword_token->type = N_ELSE;
	else if (strcmp("END", token->value.data) == 0)		keyword_token->type = N_END;
	else if (strcmp("END IF", token->value.data) == 0)	keyword_token->type = N_ENDIF;
	else if (strcmp("FOR", token->value.data) == 0)		keyword_token->type = N_FOR;
	else if (strcmp("GOTO", token->value.data) == 0)	keyword_token->type = N_GOTO;
	else if (strcmp("IF", token->value.data) == 0)		keyword_token->type = N_IF;
	else if (strcmp("INPUT", token->value.data) == 0)	keyword_token->type = N_INPUT;
	else if (strcmp("LET", token->value.data) == 0)		keyword_token->type = N_LET;
	else if (strcmp("PRINT", token->value.data) == 0)	keyword_token->type = N_PRINT;
	else if (strcmp("REM", token->value.data) == 0)		keyword_token->type = N_REM;
	else if (strcmp("WEND", token->value.data) == 0)	keyword_token->type = N_WEND;
	else if (strcmp("WHILE", token->value.data) == 0)	keyword_token->type = N_WHILE;

	(*index)++;
	return keyword_token;
}